#include "SGameActorDetailTitle.h"


void SGameActorDetailTitle::Construct(const FArguments & InArgs)
{

	ChildSlot
		[
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
		];

}