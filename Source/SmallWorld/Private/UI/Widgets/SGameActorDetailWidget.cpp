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

	TopSlot->AttachWidget
	(
		SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		.HAlign(HAlign_Left)
		.VAlign(VAlign_Center)
		.Padding(10)
		[
			SNew(STextBlock)
			.TextStyle(FGameStyle::Get(), "Text_12")
			.Text(FText::FromString(InArgs._ActorName))
		]
		+ SHorizontalBox::Slot()
		.HAlign(HAlign_Left)
		.VAlign(VAlign_Center)
		.Padding(10)
		[
			SNew(STextBlock)
			.TextStyle(FGameStyle::Get(), "Text_12")
			.Text(FText::FromString(InArgs._ActorLevel))
		]
		+ SHorizontalBox::Slot()
		.HAlign(HAlign_Left)
		.VAlign(VAlign_Center)
		.Padding(10)
		[
			SNew(STextBlock)
			.TextStyle(FGameStyle::Get(), "Text_12")
			.Text(FText::FromString(InArgs._ActorHealth))
		]
	);

	if (InArgs._DetailWidget.IsValid())
	{
		MiddleSlot->AttachWidget(InArgs._DetailWidget.ToSharedRef());
	}
}