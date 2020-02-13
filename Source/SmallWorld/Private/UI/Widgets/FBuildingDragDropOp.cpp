#include "FBuildingDragDropOp.h"



TSharedRef<FBuildingDragDropOp> FBuildingDragDropOp::New(FString temIconName)
{

	TSharedRef<FBuildingDragDropOp> Operation = MakeShared<FBuildingDragDropOp>();
	Operation->IconName = temIconName;
	//Operation->MouseCursor = EMouseCursor::Crosshairs;

	Operation->Construct();

	return Operation;
}
void FBuildingDragDropOp::OnDragged(const class FDragDropEvent& DragDropEvent)
{
	if (CursorDecoratorWindow.IsValid())
	{
		//CursorDecoratorWindow->MoveWindowTo(DragDropEvent.GetScreenSpacePosition() + FSlateApplicationBase::Get().GetCursorSize());
		
		CursorDecoratorWindow->MoveWindowTo(DragDropEvent.GetScreenSpacePosition()- CursorDecoratorWindow->GetContent()->GetDesiredSize() * 0.5f);
	}
}
TSharedPtr<SWidget> FBuildingDragDropOp::GetDefaultDecorator() const
{
	FString IconBrush = FString::Printf(TEXT("Icon.%s0"), *IconName);

	return  /*SNew(SBox)
.HAlign(HAlign_Center)
.VAlign(VAlign_Center)
[*/
	SNew(SBorder)
	.BorderBackgroundColor(FGameStyle::Get().GetColor("Color.7F6E6F70"))
		.BorderImage(FCoreStyle::Get().GetBrush("GenericWhiteBox"))
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
		.HAlign(HAlign_Left)
		.AutoWidth()
		[
			SNew(SImage)
			.Image(FGameStyle::Get().GetBrush(*IconBrush))
		]
		]
//]
		;
}