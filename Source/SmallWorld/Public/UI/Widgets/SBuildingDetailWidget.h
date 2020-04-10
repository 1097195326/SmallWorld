#pragma once

#include "SGameActorDetailWidget.h"



class SBuildingDetailWidget : public SGameActorDetailWidget
{
public:
	SLATE_BEGIN_ARGS(SBuildingDetailWidget) :
		_BuildingName(TEXT("")),
		_BuildingLevel(TEXT("")),
		_BuildingLife(TEXT("")),
		_DetailWidget(),
		_NeedOperation(false)
	{}
	SLATE_ARGUMENT(FString,BuildingName)
	SLATE_ARGUMENT(FString, BuildingLevel)
	SLATE_ARGUMENT(FString, BuildingLife)
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