#pragma once
#include "SBaseCompoundWidget.h"

class SGameActorDetailWidget : public SBaseCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SGameActorDetailWidget):
		_TitleWidget(),
		_DetailWidget(),
		_OperationWidget()
	{}
		SLATE_ARGUMENT(TSharedPtr<SWidget>, TitleWidget)
		SLATE_ARGUMENT(TSharedPtr<SWidget>, DetailWidget)
		SLATE_ARGUMENT(TSharedPtr<SWidget>, OperationWidget)

	SLATE_END_ARGS()

	void Construct(const FArguments & InArgs);

protected:
	
	SVerticalBox::FSlot  * TopSlot = NULL;
	SVerticalBox::FSlot  * MiddleSlot = NULL;
	SVerticalBox::FSlot  * BottomSlot = NULL;
	


};