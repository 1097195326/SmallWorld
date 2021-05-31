#pragma once

#include "SWrapCompoundWidget.h"
#include "SVGameActorIcon.h"

class SBuildingIconList : public SWrapCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SBuildingIconList){}

	SLATE_ARGUMENT(TArray<FString>,IconNames)

	SLATE_END_ARGS()

	void Construct(const FArguments & InArgs);

	virtual void OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;
	virtual void OnDragLeave(const FDragDropEvent& DragDropEvent) override;
	virtual FReply OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;
	virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;

protected:
	TArray<FString>			IconNames;

	TSharedPtr<SGridPanel> IconGridPanel;

};
