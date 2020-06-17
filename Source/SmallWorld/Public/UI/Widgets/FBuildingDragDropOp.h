#pragma once

#include "SBaseCompoundWidget.h"
#include "Input/DragAndDrop.h"


class FBuildingDragDropOp : public FDragDropOperation
{
public:
	DRAG_DROP_OPERATOR_TYPE(FBuildingDragDropOp, FDragDropOperation)

		static TSharedRef<FBuildingDragDropOp> New(FString IconName);

		virtual TSharedPtr<SWidget> GetDefaultDecorator() const override;
		virtual void OnDragged(const class FDragDropEvent& DragDropEvent) override;

		FString  IconName;

};