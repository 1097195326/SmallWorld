#include "FMiniMapViewportClient.h"

#include "Misc/App.h"
#include "CanvasTypes.h"
#include "Components/LineBatchComponent.h"
#include "Engine/LocalPlayer.h"
#include "EngineUtils.h"
#include "Framework/Application/SlateApplication.h"
#include "Widgets/SViewport.h"
#include "PreviewScene.h"
#include "EngineModule.h"
#include "Slate/SceneViewport.h"
#include "LegacyScreenPercentageDriver.h"
#include "UnrealEngine.h"

#define MIN_ORTHOZOOM				250.0					/* Limit of 2D viewport zoom in */
#define MAX_ORTHOZOOM				MAX_FLT					/* Limit of 2D viewport zoom out */


namespace FocusConstants
{
	const float TransitionTime = 0.25f;
}

FMiniMapViewportCameraTransform::FMiniMapViewportCameraTransform()
	: TransitionStartTime(0)
	, ViewLocation(FVector::ZeroVector)
	, ViewRotation(FRotator::ZeroRotator)
	, DesiredLocation(FVector::ZeroVector)
	, LookAt(FVector::ZeroVector)
	, StartLocation(FVector::ZeroVector)
	, OrthoZoom(DEFAULT_ORTHOZOOM)
	
{}

void FMiniMapViewportCameraTransform::SetLocation(const FVector& Position)
{
	ViewLocation = Position;
	DesiredLocation = ViewLocation;
}

void FMiniMapViewportCameraTransform::TransitionToLocation(const FVector& InDesiredLocation, bool bInstant)
{
	if (bInstant)
	{
		SetLocation(InDesiredLocation);
		TransitionStartTime = FSlateApplication::Get().GetCurrentTime() - FocusConstants::TransitionTime;
	}
	else
	{
		DesiredLocation = InDesiredLocation;
		StartLocation = ViewLocation;

		TransitionStartTime = FSlateApplication::Get().GetCurrentTime();
	}
}

bool FMiniMapViewportCameraTransform::UpdateTransition()
{
	bool bIsAnimating = false;
	double TransitionProgress = FMath::Clamp((FSlateApplication::Get().GetCurrentTime() - TransitionStartTime) / FocusConstants::TransitionTime, 0.0, 1.0);
	if (TransitionProgress < 1.0 || ViewLocation != DesiredLocation)
	{
		const float Offset = (float)TransitionProgress - 1.0f;
		float LerpWeight = Offset * Offset * Offset + 1.0f;

		if (LerpWeight == 1.0f)
		{
			// Failsafe for the value not being exact on lerps
			ViewLocation = DesiredLocation;
		}
		else
		{
			ViewLocation = FMath::Lerp(StartLocation, DesiredLocation, LerpWeight);
		}


		bIsAnimating = true;
	}

	return bIsAnimating;
}

FMatrix FMiniMapViewportCameraTransform::ComputeOrbitMatrix() const
{
	FTransform Transform =
		FTransform(-LookAt) *
		FTransform(FRotator(0, ViewRotation.Yaw, 0)) *
		FTransform(FRotator(0, 0, ViewRotation.Pitch)) *
		FTransform(FVector(0, (ViewLocation - LookAt).Size(), 0));

	return Transform.ToMatrixNoScale() * FInverseRotationMatrix(FRotator(0, 90.f, 0));
}

// -------------


FMiniMapViewportClient::FMiniMapViewportClient(FPreviewScene* InPreviewScene)
	: PreviewScene(InPreviewScene)
	, Viewport(nullptr)
	, EngineShowFlags(ESFIM_Game)
	, ViewportType(LVT_OrthoXY)
	, NearPlane(-1.0f)
	, FarPlane(0.0f)
	, ViewFOV(90.0f)
	, FOVAngle(90.0f)
	, AspectRatio(1.777777f)
	, bUsingOrbitCamera(false)
	, bUseControllingActorViewInfo(false)
	, bIsSetLookAtBox(false)

{
	ViewState.Allocate();
	ViewInfo.ProjectionMode = ECameraProjectionMode::Orthographic;
	BackgroundColor = FColor(55, 55, 55);
	GetViewTransform().SetLocation(FVector(0,0,150));
	GetViewTransform().SetLookAt(FVector(0));
}

FMiniMapViewportClient::~FMiniMapViewportClient()
{
}
void FMiniMapViewportClient::SetLookAtBox(FBox InBox)
{
	DesignLookAtBox = InBox;
	bIsSetLookAtBox = true;
}
void FMiniMapViewportClient::Tick(float InDeltaTime)
{
	if (!GIntraFrameDebuggingGameThread)
	{
		// Begin Play
		UWorld* PreviewWorld = PreviewScene->GetWorld();
		if (!PreviewWorld->bBegunPlay)
		{
			for (FActorIterator It(PreviewWorld); It; ++It)
			{
				It->DispatchBeginPlay();
			}
			PreviewWorld->bBegunPlay = true;
		}

		// Tick
		PreviewWorld->Tick(LEVELTICK_All, InDeltaTime);
	}
}

void FMiniMapViewportClient::Draw(FViewport* InViewport, FCanvas* Canvas)
{
	FViewport* ViewportBackup = Viewport;
	Viewport = InViewport ? InViewport : Viewport;

	if (bIsSetLookAtBox && Viewport && Viewport->GetSizeXY().X > 0 && Viewport->GetSizeXY().Y > 0)
	{
		bIsSetLookAtBox = false;
		if (IsPerspective())
		{
		}
		else
		{
			SetViewLocation(DesignLookAtBox.GetCenter());
			FocusViewportOnBox(DesignLookAtBox);
		}
	}
	// Determine whether we should use world time or real time based on the scene.
	float TimeSeconds;
	float RealTimeSeconds;
	float DeltaTimeSeconds;

	const bool bIsRealTime = true;

	UWorld* World = GWorld;
	if (bIsRealTime || GetScene() != World->Scene)
	{
		// Use time relative to start time to avoid issues with float vs double
		TimeSeconds = FApp::GetCurrentTime() - GStartTime;
		RealTimeSeconds = FApp::GetCurrentTime() - GStartTime;
		DeltaTimeSeconds = FApp::GetDeltaTime();
	}
	else
	{
		TimeSeconds = World->GetTimeSeconds();
		RealTimeSeconds = World->GetRealTimeSeconds();
		DeltaTimeSeconds = World->GetDeltaSeconds();
	}

	// Setup a FSceneViewFamily/FSceneView for the viewport.
	FSceneViewFamilyContext ViewFamily(FSceneViewFamily::ConstructionValues(
		Canvas->GetRenderTarget(),
		GetScene(),
		EngineShowFlags)
		.SetWorldTimes(TimeSeconds, DeltaTimeSeconds, RealTimeSeconds)
		.SetRealtimeUpdate(bIsRealTime));

	// Get DPI derived view fraction.
	float GlobalResolutionFraction = GetDPIDerivedResolutionFraction();

	// Force screen percentage show flag for High DPI.
	ViewFamily.EngineShowFlags.ScreenPercentage = true;

	if (IsPerspective())
	{
	}
	else
	{
		ViewFamily.EngineShowFlags.DisableAdvancedFeatures();
		//ESplitScreenType::Type SplitScreenConfig = GetCurrentSplitscreenConfiguration();
		ViewFamily.ViewMode = VMI_Unlit;
		EngineShowFlagOverride(ESFIM_Game, ViewFamily.ViewMode, ViewFamily.EngineShowFlags, false);
		EngineShowFlagOrthographicOverride(IsPerspective(), ViewFamily.EngineShowFlags);
		ViewFamily.EngineShowFlags.SetAntiAliasing(true);
		ViewFamily.EngineShowFlags.SetWireframe(false);
		ViewFamily.EngineShowFlags.SetBloom(false);
		ViewFamily.EngineShowFlags.SetVisualizeHDR(false);
		ViewFamily.EngineShowFlags.PostProcessing = false;
		ViewFamily.EngineShowFlags.Lighting = false;
	}
	//UpdateLightingShowFlags(ViewFamily.EngineShowFlags);
	//ViewFamily.ExposureSettings = ExposureSettings;
	//ViewFamily.LandscapeLODOverride = LandscapeLODOverride;

	FSceneView* View = CalcSceneView(&ViewFamily);

	ViewFamily.SetScreenPercentageInterface(new FLegacyScreenPercentageDriver(
		ViewFamily, GlobalResolutionFraction, /* AllowPostProcessSettingsScreenPercentage = */ false));

	//SetupViewForRendering(ViewFamily, *View);

	FSlateRect SafeFrame;
	View->CameraConstrainedViewRect = View->UnscaledViewRect;
	//if ( CalculateEditorConstrainedViewRect(SafeFrame, Viewport) )
	//{
	//	View->CameraConstrainedViewRect = FIntRect(SafeFrame.Left, SafeFrame.Top, SafeFrame.Right, SafeFrame.Bottom);
	//}

	if (IsAspectRatioConstrained())
	{
		// Clear the background to black if the aspect ratio is constrained, as the scene view won't write to all pixels.
		Canvas->Clear(FLinearColor::Black);
	}

	Canvas->Clear(BackgroundColor);

	// workaround for hacky renderer code that uses GFrameNumber to decide whether to resize render targets
	--GFrameNumber;
	GetRendererModule().BeginRenderingViewFamily(Canvas, &ViewFamily);

	// Remove temporary debug lines.
	// Possibly a hack. Lines may get added without the scene being rendered etc.
	if (World->LineBatcher != NULL && (World->LineBatcher->BatchedLines.Num() || World->LineBatcher->BatchedPoints.Num()))
	{
		World->LineBatcher->Flush();
	}

	if (World->ForegroundLineBatcher != NULL && (World->ForegroundLineBatcher->BatchedLines.Num() || World->ForegroundLineBatcher->BatchedPoints.Num()))
	{
		World->ForegroundLineBatcher->Flush();
	}

	Viewport = ViewportBackup;
}
void FMiniMapViewportClient::Draw(const FSceneView* View, FPrimitiveDrawInterface* PDI)
{

}
FSceneInterface* FMiniMapViewportClient::GetScene() const
{
	UWorld* World = GetWorld();
	if (World)
	{
		return World->Scene;
	}

	return NULL;
}

UWorld* FMiniMapViewportClient::GetWorld() const
{
	UWorld* OutWorldPtr = NULL;
	// If we have a valid scene get its world
	if (PreviewScene)
	{
		OutWorldPtr = PreviewScene->GetWorld();
	}
	if (OutWorldPtr == NULL)
	{
		OutWorldPtr = GWorld;
	}
	return OutWorldPtr;
}

bool FMiniMapViewportClient::IsAspectRatioConstrained() const
{
	return ViewInfo.bConstrainAspectRatio;
}

void FMiniMapViewportClient::SetBackgroundColor(FLinearColor InBackgroundColor)
{
	BackgroundColor = InBackgroundColor;
}

FLinearColor FMiniMapViewportClient::GetBackgroundColor() const
{
	return BackgroundColor;
}
bool FMiniMapViewportClient::IsPerspective() const
{
	return (GetViewportType() == LVT_Perspective);
}
bool FMiniMapViewportClient::IsOrtho() const
{
	return !IsPerspective();
}
FMiniMapViewportClient::EMiniMapViewportType FMiniMapViewportClient::GetViewportType() const
{
	EMiniMapViewportType EffectiveViewportType = ViewportType;
	if (bUseControllingActorViewInfo)
	{
		EffectiveViewportType = (ViewInfo.ProjectionMode == ECameraProjectionMode::Perspective) ? LVT_Perspective : LVT_OrthoFreelook;
	}
	return EffectiveViewportType;
}

void FMiniMapViewportClient::SetViewportType(EMiniMapViewportType InViewportType)
{
	ViewportType = InViewportType;

}

float FMiniMapViewportClient::GetOrthoUnitsPerPixel(const FViewport* InViewport) const
{
	const float SizeX = InViewport->GetSizeXY().X;

	// 15.0f was coming from the CAMERA_ZOOM_DIV marco, seems it was chosen arbitrarily
	//return (GetOrthoZoom() / (SizeX * 15.f))/* * ComputeOrthoZoomFactor(SizeX)*/;
	return GetOrthoZoom() / SizeX/* * ComputeOrthoZoomFactor(SizeX)*/;
}
FMatrix FMiniMapViewportClient::CalcViewRotationMatrix(const FRotator& InViewRotation) const
{
	const FMiniMapViewportCameraTransform& ViewTransform = GetViewTransform();

	if (bUsingOrbitCamera)
	{
		// @todo vreditor: Not stereo friendly yet
		return FTranslationMatrix(ViewTransform.GetLocation()) * ViewTransform.ComputeOrbitMatrix();
	}
	else
	{
		// Create the view matrix
		return FInverseRotationMatrix(InViewRotation);
	}
}
float FMiniMapViewportClient::GetNearClipPlane() const
{
	return (NearPlane < 0.0f) ? GNearClippingPlane : NearPlane;
}
void FMiniMapViewportClient::OverrideNearClipPlane(float InNearPlane)
{
	NearPlane = InNearPlane;
}
float FMiniMapViewportClient::GetFarClipPlaneOverride() const
{
	return FarPlane;
}

void FMiniMapViewportClient::OverrideFarClipPlane(const float InFarPlane)
{
	FarPlane = InFarPlane;
}
bool FMiniMapViewportClient::InputKey(FViewport* InViewport, int32 ControllerId, FKey Key, EInputEvent Event, float AmountDepressed /* = 1.f */, bool bGamepad /* = false */)
{
	if (Key == EKeys::MouseScrollDown)
	{
		SetOrthoZoom(FMath::Clamp<float>(GetViewTransform().GetOrthoZoom() + 10, 10, 1800000.0f));
	}
	else if (Key == EKeys::MouseScrollUp)
	{
		SetOrthoZoom(FMath::Clamp<float>(GetViewTransform().GetOrthoZoom() - 10, 10, 1800000.0f));

	}
	return false;
}
FSceneView* FMiniMapViewportClient::CalcSceneView(FSceneViewFamily* ViewFamily)
{
	FSceneViewInitOptions ViewInitOptions;

	FMiniMapViewportCameraTransform& ViewTransform = GetViewTransform();
	const EMiniMapViewportType EffectiveViewportType = GetViewportType();

	ViewInitOptions.ViewOrigin = ViewTransform.GetLocation();
	FRotator ViewRotation = ViewTransform.GetRotation();

	FIntPoint ViewportSize = Viewport->GetSizeXY();
	FIntPoint ViewportOffset(0, 0);

	ViewInitOptions.SetViewRectangle(FIntRect(ViewportOffset, ViewportOffset + ViewportSize));

	const bool bConstrainAspectRatio = bUseControllingActorViewInfo && ViewInfo.bConstrainAspectRatio;
	const EAspectRatioAxisConstraint AspectRatioAxisConstraint = GetDefault<ULocalPlayer>()->AspectRatioAxisConstraint;

	AWorldSettings* WorldSettings = nullptr;
	if (GetScene() != nullptr && GetScene()->GetWorld() != nullptr)
	{
		WorldSettings = GetScene()->GetWorld()->GetWorldSettings();
	}
	if (WorldSettings != nullptr)
	{
		ViewInitOptions.WorldToMetersScale = WorldSettings->WorldToMeters;
	}

	if (bUseControllingActorViewInfo)
	{
		// @todo vreditor: Not stereo friendly yet
		ViewInitOptions.ViewRotationMatrix = FInverseRotationMatrix(ViewRotation) * FMatrix(
			FPlane(0, 0, 1, 0),
			FPlane(1, 0, 0, 0),
			FPlane(0, 1, 0, 0),
			FPlane(0, 0, 0, 1));

		FMinimalViewInfo::CalculateProjectionMatrixGivenView(ViewInfo, AspectRatioAxisConstraint, Viewport, /*inout*/ ViewInitOptions);
	}
	else
	{
		//
		if (EffectiveViewportType == LVT_Perspective)
		{
			// Calc view rotation matrix
			ViewInitOptions.ViewRotationMatrix = CalcViewRotationMatrix(ViewRotation);

			// Rotate view 90 degrees
			ViewInitOptions.ViewRotationMatrix = ViewInitOptions.ViewRotationMatrix * FMatrix(
			FPlane(0, 0, 1, 0),
			FPlane(1, 0, 0, 0),
			FPlane(0, 1, 0, 0),
			FPlane(0, 0, 0, 1));

			
			const float MinZ = GetNearClipPlane();
			const float MaxZ = MinZ;
			// Avoid zero ViewFOV's which cause divide by zero's in projection matrix
			const float MatrixFOV = FMath::Max(0.001f, ViewFOV) * (float)PI / 360.0f;

			if (bConstrainAspectRatio)
			{
				if ((bool)ERHIZBuffer::IsInverted)
				{
					ViewInitOptions.ProjectionMatrix = FReversedZPerspectiveMatrix(
						MatrixFOV,
						MatrixFOV,
						1.0f,
						AspectRatio,
						MinZ,
						MaxZ
					);
				}
				else
				{
					ViewInitOptions.ProjectionMatrix = FPerspectiveMatrix(
						MatrixFOV,
						MatrixFOV,
						1.0f,
						AspectRatio,
						MinZ,
						MaxZ
					);
				}
			}
			else
			{
				float XAxisMultiplier;
				float YAxisMultiplier;

				if (((ViewportSize.X > ViewportSize.Y) && (AspectRatioAxisConstraint == AspectRatio_MajorAxisFOV)) || (AspectRatioAxisConstraint == AspectRatio_MaintainXFOV))
				{
					//if the viewport is wider than it is tall
					XAxisMultiplier = 1.0f;
					YAxisMultiplier = ViewportSize.X / (float)ViewportSize.Y;
				}
				else
				{
					//if the viewport is taller than it is wide
					XAxisMultiplier = ViewportSize.Y / (float)ViewportSize.X;
					YAxisMultiplier = 1.0f;
				}

				if ((bool)ERHIZBuffer::IsInverted)
				{
					ViewInitOptions.ProjectionMatrix = FReversedZPerspectiveMatrix(
						MatrixFOV,
						MatrixFOV,
						XAxisMultiplier,
						YAxisMultiplier,
						MinZ,
						MaxZ
					);
				}
				else
				{
					ViewInitOptions.ProjectionMatrix = FPerspectiveMatrix(
						MatrixFOV,
						MatrixFOV,
						XAxisMultiplier,
						YAxisMultiplier,
						MinZ,
						MaxZ
					);
				}
			}
		}
		else
		{
			static_assert((bool)ERHIZBuffer::IsInverted, "Check all the Rotation Matrix transformations!");
			float ZScale = 0.5f / HALF_WORLD_MAX;
			float ZOffset = HALF_WORLD_MAX;

			//The divisor for the matrix needs to match the translation code.
			const float Zoom = GetOrthoUnitsPerPixel(Viewport);

			float OrthoWidth = Zoom * ViewportSize.X / 2.0f;
			float OrthoHeight = Zoom * ViewportSize.Y / 2.0f;

			if (EffectiveViewportType == LVT_OrthoXY)
			{
				ViewInitOptions.ViewRotationMatrix = FMatrix(
					FPlane(1, 0, 0, 0),
					FPlane(0, -1, 0, 0),
					FPlane(0, 0, -1, 0),
					FPlane(0, 0, -ViewInitOptions.ViewOrigin.Z, 1));
			}
			else if (EffectiveViewportType == LVT_OrthoXZ)
			{
				ViewInitOptions.ViewRotationMatrix = FMatrix(
					FPlane(1, 0, 0, 0),
					FPlane(0, 0, -1, 0),
					FPlane(0, 1, 0, 0),
					FPlane(0, 0, -ViewInitOptions.ViewOrigin.Y, 1));
			}
			else if (EffectiveViewportType == LVT_OrthoYZ)
			{
				ViewInitOptions.ViewRotationMatrix = FMatrix(
					FPlane(0, 0, 1, 0),
					FPlane(1, 0, 0, 0),
					FPlane(0, 1, 0, 0),
					FPlane(0, 0, ViewInitOptions.ViewOrigin.X, 1));
			}
			else if (EffectiveViewportType == LVT_OrthoNegativeXY)
			{
				ViewInitOptions.ViewRotationMatrix = FMatrix(
					FPlane(-1, 0, 0, 0),
					FPlane(0, -1, 0, 0),
					FPlane(0, 0, 1, 0),
					FPlane(0, 0, -ViewInitOptions.ViewOrigin.Z, 1));
			}
			else if (EffectiveViewportType == LVT_OrthoNegativeXZ)
			{
				ViewInitOptions.ViewRotationMatrix = FMatrix(
					FPlane(-1, 0, 0, 0),
					FPlane(0, 0, 1, 0),
					FPlane(0, 1, 0, 0),
					FPlane(0, 0, -ViewInitOptions.ViewOrigin.Y, 1));
			}
			else if (EffectiveViewportType == LVT_OrthoNegativeYZ)
			{
				ViewInitOptions.ViewRotationMatrix = FMatrix(
					FPlane(0, 0, -1, 0),
					FPlane(-1, 0, 0, 0),
					FPlane(0, 1, 0, 0),
					FPlane(0, 0, ViewInitOptions.ViewOrigin.X, 1));
			}
			else if (EffectiveViewportType == LVT_OrthoFreelook)
			{
				ViewInitOptions.ViewRotationMatrix = FMatrix(
					FPlane(0, 0, 1, 0),
					FPlane(1, 0, 0, 0),
					FPlane(0, 1, 0, 0),
					FPlane(0, 0, ViewInitOptions.ViewOrigin.X, 1));
			}
			else
			{
				// Unknown viewport type
				check(false);
			}

			ViewInitOptions.ProjectionMatrix = FReversedZOrthoMatrix(
				OrthoWidth,
				OrthoHeight,
				ZScale,
				ZOffset
			);

		}

		if (bConstrainAspectRatio)
		{
			ViewInitOptions.SetConstrainedViewRectangle(Viewport->CalculateViewExtents(AspectRatio, ViewInitOptions.GetViewRect()));
		}
	}

	ViewInitOptions.ViewFamily = ViewFamily;
	ViewInitOptions.SceneViewStateInterface = ViewState.GetReference();
	
	ViewInitOptions.ViewElementDrawer = this;

	ViewInitOptions.BackgroundColor = GetBackgroundColor();

	// for ortho views to steal perspective view origin
	//ViewInitOptions.OverrideLODViewOrigin = FVector::ZeroVector;
	//ViewInitOptions.bUseFauxOrthoViewPos = true;

	//ViewInitOptions.FOV = ViewFOV;
	if (bUseControllingActorViewInfo)
	{
		ViewInitOptions.bUseFieldOfViewForLOD = ViewInfo.bUseFieldOfViewForLOD;
		ViewInitOptions.FOV = ViewInfo.FOV;
	}

	//ViewInitOptions.OverrideFarClippingPlaneDistance = FarPlane;
	//ViewInitOptions.CursorPos = CurrentMousePos;

	FSceneView* View = new FSceneView(ViewInitOptions);

	View->ViewLocation = ViewTransform.GetLocation();
	View->ViewRotation = ViewRotation;
	//View->SubduedSelectionOutlineColor = GEngine->GetSubduedSelectionOutlineColor();

	ViewFamily->Views.Add(View);

	View->StartFinalPostprocessSettings(View->ViewLocation);

	OverridePostProcessSettings(*View);
	
	View->EndFinalPostprocessSettings(ViewInitOptions);

	return View;
}

void FMiniMapViewportClient::FocusViewportOnBox(const FBox& BoundingBox, bool bInstant /* = false */)
{
	const FVector Position = BoundingBox.GetCenter();
	float Radius = FMath::Max(BoundingBox.GetExtent().Size(), 10.f);

	float AspectToUse = AspectRatio;
	FIntPoint ViewportSize = Viewport->GetSizeXY();
	if (!bUseControllingActorViewInfo && ViewportSize.X > 0 && ViewportSize.Y > 0)
	{
		AspectToUse = Viewport->GetDesiredAspectRatio();
	}

	const bool bEnable = false;
	ToggleOrbitCamera(bEnable);

	{
		FMiniMapViewportCameraTransform& ViewTransform = GetViewTransform();

		if (!IsOrtho())
		{
			/**
			* We need to make sure we are fitting the sphere into the viewport completely, so if the height of the viewport is less
			* than the width of the viewport, we scale the radius by the aspect ratio in order to compensate for the fact that we have
			* less visible vertically than horizontally.
			*/
			if (AspectToUse > 1.0f)
			{
				Radius *= AspectToUse;
			}

			/**
			* Now that we have a adjusted radius, we are taking half of the viewport's FOV,
			* converting it to radians, and then figuring out the camera's distance from the center
			* of the bounding sphere using some simple trig.  Once we have the distance, we back up
			* along the camera's forward vector from the center of the sphere, and set our new view location.
			*/

			const float HalfFOVRadians = FMath::DegreesToRadians(ViewFOV / 2.0f);
			const float DistanceFromSphere = Radius / FMath::Tan(HalfFOVRadians);
			FVector CameraOffsetVector = ViewTransform.GetRotation().Vector() * -DistanceFromSphere;

			ViewTransform.SetLookAt(Position);
			//ViewTransform.TransitionToLocation(Position + CameraOffsetVector, EditorViewportWidget, bInstant);

		}
		else
		{
			// For ortho viewports just set the camera position to the center of the bounding volume.
			//SetViewLocation( Position );
			//ViewTransform.TransitionToLocation(Position, EditorViewportWidget, bInstant);

			if (!(Viewport->KeyState(EKeys::LeftControl) || Viewport->KeyState(EKeys::RightControl)))
			{
				/**
				* We also need to zoom out till the entire volume is in view.  The following block of code first finds the minimum dimension
				* size of the viewport.  It then calculates backwards from what the view size should be (The radius of the bounding volume),
				* to find the new OrthoZoom value for the viewport. The 15.0f is a fudge factor.
				*/
				float NewOrthoZoom;
				uint32 MinAxisSize = (AspectToUse > 1.0f) ? Viewport->GetSizeXY().Y : Viewport->GetSizeXY().X;
				float Zoom = Radius / (MinAxisSize / 2.0f);

				NewOrthoZoom = Zoom * (Viewport->GetSizeXY().X*15.0f);
				NewOrthoZoom = FMath::Clamp<float>(NewOrthoZoom, MIN_ORTHOZOOM, MAX_ORTHOZOOM);
				ViewTransform.SetOrthoZoom(NewOrthoZoom);
			}
		}
	}

	// Tell the viewport to redraw itself.
	Invalidate();
}

void FMiniMapViewportClient::Invalidate(bool bInvalidateChildViews, bool bInvalidateHitProxies)
{
	if (Viewport)
	{
		if (bInvalidateHitProxies)
		{
			// Invalidate hit proxies and display pixels.
			Viewport->Invalidate();
		}
		else
		{
			// Invalidate only display pixels.
			Viewport->InvalidateDisplay();
		}

		// If this viewport is a view parent . . .
		/*if (bInvalidateChildViews &&
			ViewState.GetReference()->IsViewParent())
		{
			GEditor->InvalidateChildViewports(ViewState.GetReference(), bInvalidateHitProxies);
		}*/
	}
}

void FMiniMapViewportClient::ToggleOrbitCamera(bool bEnableOrbitCamera)
{
	if (bUsingOrbitCamera != bEnableOrbitCamera)
	{
		FMiniMapViewportCameraTransform& ViewTransform = GetViewTransform();

		bUsingOrbitCamera = bEnableOrbitCamera;

		// Convert orbit view to regular view
		FMatrix OrbitMatrix = ViewTransform.ComputeOrbitMatrix();
		OrbitMatrix = OrbitMatrix.InverseFast();

		if (!bUsingOrbitCamera)
		{
			// Ensure that the view location and rotation is up to date to ensure smooth transition in and out of orbit mode
			ViewTransform.SetRotation(OrbitMatrix.Rotator());
		}
		else
		{
			FRotator ViewRotation = ViewTransform.GetRotation();

			bool bUpsideDown = (ViewRotation.Pitch < -90.0f || ViewRotation.Pitch > 90.0f || !FMath::IsNearlyZero(ViewRotation.Roll, KINDA_SMALL_NUMBER));

			// if the camera is upside down compute the rotation differently to preserve pitch
			// otherwise the view will pop to right side up when transferring to orbit controls
			if (bUpsideDown)
			{
				FMatrix OrbitViewMatrix = FTranslationMatrix(-ViewTransform.GetLocation());
				OrbitViewMatrix *= FInverseRotationMatrix(ViewRotation);
				OrbitViewMatrix *= FRotationMatrix(FRotator(0, 90.f, 0));

				FMatrix RotMat = FTranslationMatrix(-ViewTransform.GetLookAt()) * OrbitViewMatrix;
				FMatrix RotMatInv = RotMat.InverseFast();
				FRotator RollVec = RotMatInv.Rotator();
				FMatrix YawMat = RotMatInv * FInverseRotationMatrix(FRotator(0, 0, -RollVec.Roll));
				FMatrix YawMatInv = YawMat.InverseFast();
				FRotator YawVec = YawMat.Rotator();
				FRotator rotYawInv = YawMatInv.Rotator();
				ViewTransform.SetRotation(FRotator(-RollVec.Roll, YawVec.Yaw, 0));
			}
			else
			{
				ViewTransform.SetRotation(OrbitMatrix.Rotator());
			}
		}

		ViewTransform.SetLocation(OrbitMatrix.GetOrigin());
	}
}