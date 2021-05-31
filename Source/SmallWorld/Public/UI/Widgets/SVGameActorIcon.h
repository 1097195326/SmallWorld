#pragma once

#include "SWrapCompoundWidget.h"


class SVGameActorIcon : public SWrapCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SVGameActorIcon){}

	SLATE_ARGUMENT(FString,IconName)

	SLATE_END_ARGS()

	void Construct(const FArguments & InArgs);
	~SVGameActorIcon();

	void RefreshView();

	void OnDataChanged();

	virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	
	virtual FReply OnTouchStarted(const FGeometry& MyGeometry, const FPointerEvent& InTouchEvent) override;

	virtual FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;

protected:
	FSlateBrush Brush;

	FDelegateHandle  GoldDelegateHandle;
	FDelegateHandle  StoneDelegateHandle;
	FDelegateHandle  WoodDelegateHandle;

	TSharedPtr<SImage> IconImage;
	TSharedPtr<SButton> IconButton;
	TSharedPtr<STextBlock> IconText;

	FString IconName;

};