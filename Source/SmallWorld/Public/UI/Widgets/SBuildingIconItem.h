#pragma once

#include "SBaseCompoundWidget.h"


class SBuildingIconItem : public SBaseCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SBuildingIconItem){}

	SLATE_ARGUMENT(FString,IconName)

	SLATE_END_ARGS()

	void Construct(const FArguments & InArgs);
	~SBuildingIconItem();

	void RefreshView();

	void OnDataChanged();

	virtual FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;

protected:
	FDelegateHandle  GoldDelegateHandle;
	FDelegateHandle  StoneDelegateHandle;
	FDelegateHandle  WoodDelegateHandle;

	TSharedPtr<SImage> IconImage;
	TSharedPtr<SButton> IconButton;
	TSharedPtr<STextBlock> IconText;

	FString IconName;

};