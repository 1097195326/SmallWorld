#pragma once


#include "SBaseCompoundWidget.h"
#include "SBuildingIconItem.h"

class SServiceDragDropWidget : public SBaseCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SServiceDragDropWidget) {}

	SLATE_END_ARGS()

	void Construct(const FArguments & InArgs);


	virtual void OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;
	virtual void OnDragLeave(const FDragDropEvent& DragDropEvent) override;
	virtual FReply OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;
	virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;

protected:
	

};
