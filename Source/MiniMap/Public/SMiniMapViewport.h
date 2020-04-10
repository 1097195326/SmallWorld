#pragma once

#include "Widgets/SViewport.h"
#include "Slate/SceneViewport.h"
#include "FMiniMapViewportClient.h"
#include "Engine/Public/PreviewScene.h"


class FPreviewScene;

class SMiniMapViewport : public SViewport
{
public:
	SLATE_BEGIN_ARGS(SMiniMapViewport)
	{
	}
	SLATE_END_ARGS()

	SMiniMapViewport();

	void Construct(const FArguments& InArgs);

	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;

	TSharedPtr<FMiniMapViewportClient> ViewportClient;

	TSharedPtr<FSceneViewport> Viewport;

	/** preview scene */
	FPreviewScene PreviewScene;
};
