#pragma once

#include "SWrapCompoundWidget.h"



class SGameActorOperation : public SWrapCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SGameActorOperation)
	{}
	
	SLATE_END_ARGS()

	void Construct(const FArguments & InArgs);

protected:
	FReply  OnUpgradeButtonClicked();
	FReply	OnMoveButtonClicked();
	FReply	OnRotationButtonClicked();
	FReply	OnClearButtonClicked();


};