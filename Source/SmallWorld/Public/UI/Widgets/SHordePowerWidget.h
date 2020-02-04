#pragma once

#include "SBaseCompoundWidget.h"


class SHordePowerWidget : public SBaseCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SHordePowerWidget){}

	SLATE_EVENT(FOnClicked, OnPowerClicked)
	SLATE_EVENT(FOnClicked, OnHeroClicked)

	SLATE_END_ARGS()
	
	void Construct(const FArguments& InArgs);
	
	
protected:
	TSharedPtr<SVerticalBox> VerticalBox;


};