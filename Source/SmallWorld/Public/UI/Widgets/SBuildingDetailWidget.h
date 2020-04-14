#pragma once

#include "SGameActorDetailWidget.h"



class SBuildingDetailWidget : public SGameActorDetailWidget
{
public:
	SLATE_BEGIN_ARGS(SBuildingDetailWidget) :
		_ActorName(TEXT("")),
		_ActorLevel(TEXT("")),
		_ActorHealth(TEXT("")),
		_DetailWidget(),
		_NeedOperation(false)
	{}
	SLATE_ARGUMENT(FString, ActorName)
	SLATE_ARGUMENT(FString, ActorLevel)
	SLATE_ARGUMENT(FString, ActorHealth)
	SLATE_ARGUMENT(TSharedPtr<SWidget>,DetailWidget)
	SLATE_ARGUMENT(bool, NeedOperation)

	SLATE_END_ARGS()

	void Construct(const FArguments & InArgs);

protected:
	FReply  OnUpgradeButtonClicked();
	FReply	OnMoveButtonClicked();
	FReply	OnRotationButtonClicked();
	FReply	OnClearButtonClicked();

	bool	bNeedOperation;




};