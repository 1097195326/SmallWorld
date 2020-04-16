#pragma once
#include "SBaseCompoundWidget.h"
#include "SMiniMapViewport.h"


class SMiniMapWidget : public SBaseCompoundWidget
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
