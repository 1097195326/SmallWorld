#pragma once
#include "SBaseCompoundWidget.h"

class SBuildingDetailWidget : public SBaseCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SBuildingDetailWidget):
		_NeedOperation(false)
	{}

	SLATE_ARGUMENT(bool,NeedOperation)

	SLATE_END_ARGS()

	void Construct(const FArguments & InArgs);

protected:
	FReply  OnUpgradeButtonClicked();
	FReply	OnMoveButtonClicked();
	FReply	OnRotationButtonClicked();
	FReply	OnClearButtonClicked();

	bool	bNeedOperation;

	SVerticalBox::FSlot  * TopSlot = NULL;
	SVerticalBox::FSlot  * MiddleSlot = NULL;
	SVerticalBox::FSlot  * BottomSlot = NULL;
	


};