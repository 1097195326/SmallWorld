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
void SServiceDragDropWidget::OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent)
{
	TSharedPtr< FDragDropOperation> Operation = DragDropEvent.GetOperation();
	
	bool IsValidDrap = false;
	if (Operation->IsOfType<FBuildingDragDropOp>())
	{
		TSharedPtr<FBuildingDragDropOp> BuildingOperation = StaticCastSharedPtr<FBuildingDragDropOp>(Operation);
		BuildingOperation->SetDecoratorVisibility(false);

		GVC->UpdatePriviewActor(DragDropEvent.GetScreenSpacePosition(), BuildingOperation->IconName);
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
	GVC->UpdatePriviewActor(DragDropEvent.GetScreenSpacePosition());
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
		IsValidDrap = true;
	}
	if (IsValidDrap && GVC->HavePriviewActor())
	{
		GVC->DestroyPriviewActor();
		GVC->DropPriviewActor();

		return FReply::Handled();
	}
	return FReply::Unhandled();
}