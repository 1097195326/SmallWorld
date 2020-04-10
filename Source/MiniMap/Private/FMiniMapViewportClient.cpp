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
{
	ViewState.Allocate();

	BackgroundColor = FColor(55, 55, 55);
}

FMiniMapViewportClient::~FMiniMapViewportClient()
{
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

	ViewFamily.EngineShowFlags = EngineShowFlags;

	//UpdateLightingShowFlags(ViewFamily.EngineShowFlags);

	//ViewFamily.ExposureSettings = ExposureSettings;

	//ViewFamily.LandscapeLODOverride = LandscapeLODOverride;

	FSceneView* View = CalcSceneView(&ViewFamily);

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

float FMiniMapViewportClient::GetOrthoUnitsPerPixel(const FViewport* InViewport) const
{
	const float SizeX = InViewport->GetSizeXY().X;

	// 15.0f was coming from the CAMERA_ZOOM_DIV marco, seems it was chosen arbitrarily
	return (GetOrthoZoom() / (SizeX * 15.f))/* * ComputeOrthoZoomFactor(SizeX)*/;
}


FSceneView* FMiniMapViewportClient::CalcSceneView(FSceneViewFamily* ViewFamily)
{
	FSceneViewInitOptions ViewInitOptions;

	const FVector& ViewLocation = GetViewLocation();
	const FRotator& ViewRotation = GetViewRotation();

	const FIntPoint ViewportSizeXY = Viewport->GetSizeXY();

	FIntRect ViewRect = FIntRect(0, 0, ViewportSizeXY.X, ViewportSizeXY.Y);
	ViewInitOptions.SetViewRectangle(ViewRect);

	ViewInitOptions.ViewOrigin = ViewLocation;

	ViewInitOptions.ViewRotationMatrix = FInverseRotationMatrix(ViewRotation);
	ViewInitOptions.ViewRotationMatrix = ViewInitOptions.ViewRotationMatrix * FMatrix(
		FPlane(0, 0, 1, 0),
		FPlane(1, 0, 0, 0),
		FPlane(0, 1, 0, 0),
		FPlane(0, 0, 0, 1));

	//@TODO: Should probably be locally configurable (or just made into a FMinimalViewInfo property)
	const EAspectRatioAxisConstraint AspectRatioAxisConstraint = GetDefault<ULocalPlayer>()->AspectRatioAxisConstraint;

	FMinimalViewInfo::CalculateProjectionMatrixGivenView(ViewInfo, AspectRatioAxisConstraint, Viewport, /*inout*/ ViewInitOptions);

	ViewInitOptions.ViewFamily = ViewFamily;
	ViewInitOptions.SceneViewStateInterface = ViewState.GetReference();
	ViewInitOptions.ViewElementDrawer = this;

	ViewInitOptions.BackgroundColor = GetBackgroundColor();

#if WITH_EDITOR
	//ViewInitOptions.EditorViewScreenPercentage = GetEditorScreenPercentage();
#endif

	//ViewInitOptions.EditorViewBitflag = 0, // send the bit for this view - each actor will check it's visibility bits against this

	// for ortho views to steal perspective view origin
	//ViewInitOptions.OverrideLODViewOrigin = FVector::ZeroVector;
	//ViewInitOptions.bUseFauxOrthoViewPos = true;

	//ViewInitOptions.CursorPos = CurrentMousePos;

	FSceneView* View = new FSceneView(ViewInitOptions);

	ViewFamily->Views.Add(View);

	View->StartFinalPostprocessSettings(ViewLocation);

	//OverridePostProcessSettings(*View);

	View->EndFinalPostprocessSettings(ViewInitOptions);

	return View;
}
