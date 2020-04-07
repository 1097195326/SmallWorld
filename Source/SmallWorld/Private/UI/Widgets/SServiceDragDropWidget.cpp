#include "SServiceDragDropWidget.h"
#include "FBuildingDragDropOp.h"
#include "UserController.h"


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
	FVector2D ScreenPosition = MyGeometry.AbsoluteToLocal(MouseEvent.GetScreenSpacePosition()) * MyGeometry.Scale;
	AUserController::Instance->TrySelectGameActor(ScreenPosition);

	return FReply::Handled();
}
FReply SServiceDragDropWidget::OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{

	return FReply::Handled();
}
FReply SServiceDragDropWidget::OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	return FReply::Unhandled();
}
FReply SServiceDragDropWidget::OnTouchStarted(const FGeometry& MyGeometry, const FPointerEvent& InTouchEvent)
{
	return FReply::Unhandled();
}
FReply SServiceDragDropWidget::OnTouchMoved(const FGeometry& MyGeometry, const FPointerEvent& InTouchEvent)
{
	return FReply::Unhandled();
}
FReply SServiceDragDropWidget::OnTouchEnded(const FGeometry& MyGeometry, const FPointerEvent& InTouchEvent)
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
		
		AUserController::Instance->UpdatePriviewActor(CachedOnDropLocalMousePos, BuildingOperation->IconName);
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
	if (AUserController::Instance->HavePriviewActor())
	{
		AUserController::Instance->DestroyPriviewActor();
	}
}
FReply SServiceDragDropWidget::OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent)
{
	FVector2D CachedOnDropLocalMousePos = MyGeometry.AbsoluteToLocal(DragDropEvent.GetScreenSpacePosition()) * MyGeometry.Scale;

	AUserController::Instance->UpdatePriviewActor(CachedOnDropLocalMousePos);
	if (AUserController::Instance->HavePriviewActor())
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
		AUserController::Instance->DropPriviewActor();
		
		IsValidDrap = true;
	}
	if (IsValidDrap)
	{
		
		return FReply::Handled();
	}
	return FReply::Unhandled();
}