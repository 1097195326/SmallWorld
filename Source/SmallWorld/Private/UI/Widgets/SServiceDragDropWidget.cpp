#include "SServiceDragDropWidget.h"


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


}
void SServiceDragDropWidget::OnDragLeave(const FDragDropEvent& DragDropEvent)
{

}
FReply SServiceDragDropWidget::OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent)
{

	return FReply::Handled();
}
FReply SServiceDragDropWidget::OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent)
{

	return FReply::Handled();
}