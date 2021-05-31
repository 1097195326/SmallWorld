#pragma once

#include "SWrapCompoundWidget.h"


class SHordePowerWidget : public SWrapCompoundWidget
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