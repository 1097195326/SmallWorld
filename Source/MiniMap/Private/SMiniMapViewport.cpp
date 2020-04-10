#include "SMiniMapViewport.h"



SMiniMapViewport::SMiniMapViewport()
: PreviewScene(FPreviewScene::ConstructionValues().SetEditor(false))
{}
void SMiniMapViewport::Construct(const FArguments& InArgs)
{
	SViewport::FArguments ParentArgs;
	ParentArgs.IgnoreTextureAlpha(false);
	ParentArgs.EnableBlending(false);
	//ParentArgs.RenderDirectlyToWindow(true);
	SViewport::Construct(ParentArgs);
									   
	ViewportClient = MakeShareable(new FMiniMapViewportClient(&PreviewScene));
	Viewport = MakeShareable(new FSceneViewport(ViewportClient.Get(), SharedThis(this)));

	// The viewport widget needs an interface so it knows what should render
	SetViewportInterface(Viewport.ToSharedRef());
}
void SMiniMapViewport::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	Viewport->Invalidate();
	//Viewport->InvalidateDisplay();

	Viewport->Tick(AllottedGeometry, InCurrentTime, InDeltaTime);
	ViewportClient->Tick(InDeltaTime);
}

