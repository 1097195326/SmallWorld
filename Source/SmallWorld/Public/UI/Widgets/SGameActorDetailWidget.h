#pragma once
#include "SBaseCompoundWidget.h"

class SGameActorDetailWidget : public SBaseCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SGameActorDetailWidget)
	{}

	SLATE_END_ARGS()

	void Construct(const FArguments & InArgs);

protected:
	
	SVerticalBox::FSlot  * TopSlot = NULL;
	SVerticalBox::FSlot  * MiddleSlot = NULL;
	SVerticalBox::FSlot  * BottomSlot = NULL;
	


};