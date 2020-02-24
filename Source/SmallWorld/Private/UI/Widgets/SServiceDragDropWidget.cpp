#include "SServiceDragDropWidget.h"
#include "FBuildingDragDropOp.h"
#include "UserViewportClient.h"



void SServiceDragDropWidget::Construct(const FArguments & InArgs)
{
	ChildSlot
		[
			SNew(SBorder)
			.BorderBackgroundColor(FGameStyle::Get().GetColor("Color.FFFA4147"))
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

		GVC->UpdatePriviewActor(BuildingOperation->IconName);
		IsValidDrap = true;
	}
	if (IsValidDrap)
	{

	}
}
void SServiceDragDropWidget::OnDragLeave(const FDragDropEvent& DragDropEvent)
{
	if (GVC->HavePriviewActor())
	{
		GVC->DestroyPriviewActor();
	}
}
FReply SServiceDragDropWidget::OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent)
{
	if (GVC->HavePriviewActor())
	{
		GVC->UpdatePriviewActor();
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