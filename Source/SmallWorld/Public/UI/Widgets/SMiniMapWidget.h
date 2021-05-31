#pragma once
#include "SWrapCompoundWidget.h"
#include "SMiniMapViewport.h"


class SMiniMapWidget : public SWrapCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SMiniMapWidget){}

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	UWorld * GetViewportWorld() const;

	void  TestSpawnAcor();

private:

	FReply OnSwitchButtonClicked();

	TSharedPtr<SMiniMapViewport>  PreviewViewport;
	TSharedPtr<SButton>		SwitchButton;
	TSharedPtr<SScaleBox>	ViewportContiner;

	bool		IsOpening;
};
