#include "SGameActorDetailWidget.h"



void SGameActorDetailWidget::Construct(const FArguments & InArgs)
{
	ChildSlot
		[
			SNew(SVerticalBox)
			+SVerticalBox::Slot()
			.VAlign(VAlign_Bottom)
			.HAlign(HAlign_Center)
			.AutoHeight()
			.Expose(TopSlot)
			+ SVerticalBox::Slot()
			.VAlign(VAlign_Bottom)
			.HAlign(HAlign_Center)
			.AutoHeight()
			.Expose(MiddleSlot)
			+ SVerticalBox::Slot()
			.VAlign(VAlign_Bottom)
			.HAlign(HAlign_Center)
			.AutoHeight()
			.Expose(BottomSlot)
		];

	if (InArgs._TitleWidget.IsValid())
	{
		MiddleSlot->AttachWidget(InArgs._TitleWidget.ToSharedRef());
	}
	if (InArgs._DetailWidget.IsValid())
	{
		MiddleSlot->AttachWidget(InArgs._DetailWidget.ToSharedRef());
	}
	if (InArgs._OperationWidget.IsValid())
	{
		MiddleSlot->AttachWidget(InArgs._OperationWidget.ToSharedRef());
	}
}