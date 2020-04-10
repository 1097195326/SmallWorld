#pragma once
#include "SBaseCompoundWidget.h"


class SMiniMapWidget : public SBaseCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SMiniMapWidget){}

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

private:

	FReply OnSwitchButtonClicked();

	TSharedPtr<SButton>		SwitchButton;
	TSharedPtr<SScaleBox>	ViewportContiner;

	bool		IsOpening;
};
