#include "SServiceDragDropWidget.h"
#include "FBuildingDragDropOp.h"
#include "UserViewportClient.h"


void SServiceDragDropWidget::Construct(const FArguments & InArgs)
{
	ChildSlot
		[
			SNew(SBorder)
			.BorderBackgroundColor(FGameStyle::Get().GetColor("Color.None"))
			.BorderImage(FCoreStyle::Get().GetBrush("GenericWhiteBox"))
		];
}
FReply SServiceDragDropWidget::OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{

	return FReply::Unhandled();
}
void SServiceDragDropWidget::OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent)
{
	TSharedPtr< FDragDropOperation> Operation = DragDropEvent.GetOperation();
	
	bool IsValidDrap = false;
	if (Operation->IsOfType<FBuildingDragDropOp>())
	{
		TSharedPtr<FBuildingDragDropOp> BuildingOperation = StaticCastSharedPtr<FBuildingDragDropOp>(Operation);
		BuildingOperation->SetDecoratorVisibility(false);

		FVector2D CachedOnDropLocalMousePos = MyGeometry.AbsoluteToLocal(DragDropEvent.GetScreenSpacePosition()) * MyGeometry.Scale;
		
		GVC->UpdatePriviewActor(CachedOnDropLocalMousePos, BuildingOperation->IconName);
		IsValidDrap = true;
	}
	if (IsValidDrap)
	{

	}
}
void SServiceDragDropWidget::OnDragLeave(const FDragDropEvent& DragDropEvent)
{
	TSharedPtr< FDragDropOperation> Operation = DragDropEvent.GetOperation();

	bool IsValidDrap = false;
	if (Operation->IsOfType<FBuildingDragDropOp>())
	{
		TSharedPtr<FBuildingDragDropOp> BuildingOperation = StaticCastSharedPtr<FBuildingDragDropOp>(Operation);
		BuildingOperation->SetDecoratorVisibility(true);
		IsValidDrap = true;
	}
	if (IsValidDrap)
	{

	}
	if (GVC->HavePriviewActor())
	{
		GVC->DestroyPriviewActor();
	}
}
FReply SServiceDragDropWidget::OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent)
{
	FVector2D CachedOnDropLocalMousePos = MyGeometry.AbsoluteToLocal(DragDropEvent.GetScreenSpacePosition()) * MyGeometry.Scale;

	GVC->UpdatePriviewActor(CachedOnDropLocalMousePos);
	if (GVC->HavePriviewActor())
	{
		FReply::Handled();
	}
	return FReply::Unhandled();
}
FReply SServiceDragDropWidget::OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent)
{
	TSharedPtr< FDragDropOperation> Operation = DragDropEvent.GetOperation();

	bool IsValidDrap = false;
	if (Operation.IsValid() && Operation->IsOfType<FBuildingDragDropOp>())
	{
		GVC->DropPriviewActor();
		
		IsValidDrap = true;
	}
	if (IsValidDrap)
	{
		
		return FReply::Handled();
	}
	return FReply::Unhandled();
}