#include "SGameActorDetail.h"
#include "GameStyle.h"



void SGameActorDetail::Construct(const FArguments & InArgs)
{
	ChildSlot
		[
			SNew(SVerticalBox)
			+SVerticalBox::Slot()
			.VAlign(VAlign_Bottom)
			.HAlign(HAlign_Left)
			.AutoHeight()
			.Expose(TopSlot)
			+ SVerticalBox::Slot()
			.VAlign(VAlign_Bottom)
			.HAlign(HAlign_Left)
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
		TopSlot->AttachWidget(InArgs._TitleWidget.ToSharedRef());
	}
	if (InArgs._ContentWidget.IsValid())
	{
		MiddleSlot->AttachWidget(InArgs._ContentWidget.ToSharedRef());
	}
	if (InArgs._OperationWidget.IsValid())
	{
		BottomSlot->AttachWidget(InArgs._OperationWidget.ToSharedRef());
	}
}