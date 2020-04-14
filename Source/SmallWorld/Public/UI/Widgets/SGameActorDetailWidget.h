#pragma once
#include "SBaseCompoundWidget.h"

class SGameActorDetailWidget : public SBaseCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SGameActorDetailWidget):
		_ActorName(TEXT("")),
		_ActorLevel(TEXT("")),
		_ActorHealth(TEXT("")),
		_DetailWidget()
	{}
	SLATE_ARGUMENT(FString, ActorName)
	SLATE_ARGUMENT(FString, ActorLevel)
	SLATE_ARGUMENT(FString, ActorHealth)
	SLATE_ARGUMENT(TSharedPtr<SWidget>, DetailWidget)

	SLATE_END_ARGS()

	void Construct(const FArguments & InArgs);

protected:
	
	SVerticalBox::FSlot  * TopSlot = NULL;
	SVerticalBox::FSlot  * MiddleSlot = NULL;
	SVerticalBox::FSlot  * BottomSlot = NULL;
	


};