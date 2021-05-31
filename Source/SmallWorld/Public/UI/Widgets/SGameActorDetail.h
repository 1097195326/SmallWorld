#pragma once
#include "SWrapCompoundWidget.h"

class SGameActorDetail : public SWrapCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SGameActorDetail):
		_TitleWidget(),
		_ContentWidget(),
		_OperationWidget()
	{}
		SLATE_ARGUMENT(TSharedPtr<SWidget>, TitleWidget)
		SLATE_ARGUMENT(TSharedPtr<SWidget>, ContentWidget)
		SLATE_ARGUMENT(TSharedPtr<SWidget>, OperationWidget)

	SLATE_END_ARGS()

	void Construct(const FArguments & InArgs);

protected:
	
	SVerticalBox::FSlot  * TopSlot = NULL;
	SVerticalBox::FSlot  * MiddleSlot = NULL;
	SVerticalBox::FSlot  * BottomSlot = NULL;
	


};