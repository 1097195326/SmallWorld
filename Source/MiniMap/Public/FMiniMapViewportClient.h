#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/Actor.h"
#include "ShowFlags.h"
#include "Widgets/SWidget.h"
#include "UnrealClient.h"
#include "SceneTypes.h"
#include "Camera/CameraTypes.h"
#include "SceneManagement.h"



class FCanvas;
class FPreviewScene;


/**
* Stores the transformation data for the viewport camera
*/
struct MINIMAP_API FMiniMapViewportCameraTransform
{
public:
	FMiniMapViewportCameraTransform();

	/** Sets the transform's location */
	void SetLocation(const FVector& Position);

	/** Sets the transform's rotation */
	void SetRotation(const FRotator& Rotation)
	{
		ViewRotation = Rotation;
	}

	/** Sets the location to look at during orbit */
	void SetLookAt(const FVector& InLookAt)
	{
		LookAt = InLookAt;
	}

	/** Set the ortho zoom amount */
	void SetOrthoZoom(float InOrthoZoom)
	{
		OrthoZoom = InOrthoZoom;
	}


	/** @return The transform's location */
	FORCEINLINE const FVector& GetLocation() const { return ViewLocation; }

	/** @return The transform's rotation */
	FORCEINLINE const FRotator& GetRotation() const { return ViewRotation; }

	/** @return The look at point for orbiting */
	FORCEINLINE const FVector& GetLookAt() const { return LookAt; }

	/** @return The ortho zoom amount */
	FORCEINLINE float GetOrthoZoom() const { return OrthoZoom; }

	/**
	* Animates from the current location to the desired location
	*
	* @param InDesiredLocation	The location to transition to
	* @param bInstant			If the desired location should be set instantly rather than transitioned to over time
	*/
	void TransitionToLocation(const FVector& InDesiredLocation, bool bInstant);

	/**
	* Updates any current location transitions
	*
	* @return true if there is currently a transition
	*/
	bool UpdateTransition();

	/**
	* Computes a matrix to use for viewport location and rotation when orbiting
	*/
	FMatrix ComputeOrbitMatrix() const;
private:
	/** The time when a transition to the desired location began */
	double TransitionStartTime;
	/** Current viewport Position. */
	FVector	ViewLocation;
	/** Current Viewport orientation; valid only for perspective projections. */
	FRotator ViewRotation;
	/** Desired viewport location when animating between two locations */
	FVector	DesiredLocation;
	/** When orbiting, the point we are looking at */
	FVector LookAt;
	/** Viewport start location when animating to another location */
	FVector StartLocation;
	/** Ortho zoom amount */
	float OrthoZoom;
};


class MINIMAP_API FMiniMapViewportClient : public FCommonViewportClient, public FViewElementDrawer
{
public:
	enum EMiniMapViewportType
	{
		/** Top */
		LVT_OrthoXY = 0,
		/** Front */
		LVT_OrthoXZ = 1,
		/** Left */
		LVT_OrthoYZ = 2,
		LVT_Perspective = 3,
		LVT_OrthoFreelook = 4,
		/** Bottom */
		LVT_OrthoNegativeXY = 5,
		/** Back */
		LVT_OrthoNegativeXZ = 6,
		/** Right */
		LVT_OrthoNegativeYZ = 7,
		LVT_MAX,

		LVT_None = 255,
	}; 

	FMiniMapViewportClient(FPreviewScene* InPreviewScene = nullptr);
	virtual ~FMiniMapViewportClient();

	// FViewportClient interface
	virtual UWorld* GetWorld() const override;
	virtual void Draw(FViewport* InViewport, FCanvas* Canvas) override;

	//using FViewElementDrawer::Draw;
	virtual void Draw(const FSceneView* View, FPrimitiveDrawInterface* PDI) override;

	virtual bool InputKey(FViewport* InViewport, int32 ControllerId, FKey Key, EInputEvent Event, float AmountDepressed = 1.f, bool bGamepad = false) override;


	// FUMGViewportClient

	virtual void Tick(float InDeltaTime);

	virtual FSceneView* CalcSceneView(FSceneViewFamily* ViewFamily);


	/**
	* @return The scene being rendered in this viewport
	*/
	virtual FSceneInterface* GetScene() const;


	bool IsAspectRatioConstrained() const;

	void SetBackgroundColor(FLinearColor InBackgroundColor);
	FLinearColor GetBackgroundColor() const;

	/** Sets the location of the viewport's camera */
	void SetViewLocation(const FVector& NewLocation)
	{
		GetViewTransform().SetLocation(NewLocation);
	}

	/** Sets the location of the viewport's camera */
	void SetViewRotation(const FRotator& NewRotation)
	{
		GetViewTransform().SetRotation(NewRotation);
	}

	/**
	* Sets the look at location of the viewports camera for orbit *
	*
	* @param LookAt The new look at location
	* @param bRecalulateView	If true, will recalculate view location and rotation to look at the new point immediatley
	*/
	void SetLookAtLocation(const FVector& LookAt, bool bRecalculateView = false)
	{
		GetViewTransform().SetLookAt(LookAt);

		if (bRecalculateView)
		{
			FMatrix OrbitMatrix = GetViewTransform().ComputeOrbitMatrix();
			OrbitMatrix = OrbitMatrix.InverseFast();

			GetViewTransform().SetRotation(OrbitMatrix.Rotator());
			GetViewTransform().SetLocation(OrbitMatrix.GetOrigin());
		}
	}

	/** Sets ortho zoom amount */
	void SetOrthoZoom(float InOrthoZoom)
	{
		// A zero ortho zoom is not supported and causes NaN/div0 errors
		check(InOrthoZoom != 0);
		GetViewTransform().SetOrthoZoom(InOrthoZoom);
	}

	/** @return the current viewport camera location */
	const FVector& GetViewLocation() const
	{
		return GetViewTransform().GetLocation();
	}

	/** @return the current viewport camera rotation */
	const FRotator& GetViewRotation() const
	{
		return GetViewTransform().GetRotation();
	}

	/** @return the current look at location */
	const FVector& GetLookAtLocation() const
	{
		return GetViewTransform().GetLookAt();
	}

	/** @return the current ortho zoom amount */
	float GetOrthoZoom() const
	{
		return GetViewTransform().GetOrthoZoom();
	}

	/** @return The number of units per pixel displayed in this viewport */
	float GetOrthoUnitsPerPixel(const FViewport* Viewport) const;

	void SetEngineShowFlags(FEngineShowFlags InEngineShowFlags)
	{
		EngineShowFlags = InEngineShowFlags;
	}

	FMiniMapViewportCameraTransform& GetViewTransform()
	{
		return IsPerspective() ? ViewTransformPerspective : ViewTransformOrthographic;
	}

	const FMiniMapViewportCameraTransform& GetViewTransform() const
	{
		return IsPerspective() ? ViewTransformPerspective : ViewTransformOrthographic;
	}
	bool IsPerspective() const;

	virtual EMiniMapViewportType GetViewportType() const;

	virtual void SetViewportType(EMiniMapViewportType InViewportType);

	virtual FMatrix CalcViewRotationMatrix(const FRotator& InViewRotation) const;

	/** Get the near clipping plane for this viewport. */
	float GetNearClipPlane() const;

	/** Subclasses may override the near clipping plane. Set to a negative value to disable the override. */
	void OverrideNearClipPlane(float InNearPlane);

	/** Get the far clipping plane override for this viewport. */
	float GetFarClipPlaneOverride() const;

	/** Override the far clipping plane. Set to a negative value to disable the override. */
	void OverrideFarClipPlane(const float InFarPlane);

	virtual void OverridePostProcessSettings(FSceneView& View) {};

protected:

	/** The scene used for the viewport. Owned externally */
	FPreviewScene* PreviewScene;

	FMinimalViewInfo ViewInfo;

	FLinearColor BackgroundColor;

	/** Viewport camera transform data */
	FMiniMapViewportCameraTransform ViewTransformPerspective;
	FMiniMapViewportCameraTransform ViewTransformOrthographic;

	FViewport* Viewport;

	/** The viewport's scene view state. */
	FSceneViewStateReference ViewState;

	/** A set of flags that determines visibility for various scene elements. */
	FEngineShowFlags EngineShowFlags;

	EMiniMapViewportType		ViewportType;

	/** near plane adjustable for each editor view, if < 0 GNearClippingPlane should be used. */
	float NearPlane;

	/** If > 0, overrides the view's far clipping plane with a plane at the specified distance. */
	float FarPlane;

	/** Viewport's current horizontal field of view (can be modified by locked cameras etc.) */
	float ViewFOV;

	/** Viewport's stored horizontal field of view (saved in ini files). */
	float FOVAngle;

	float AspectRatio;

	bool bUsingOrbitCamera;

	bool bUseControllingActorViewInfo;

};
