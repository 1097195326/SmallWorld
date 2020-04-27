#include "SHorizontalIconTextItem.h"



void SHorizontalIconTextItem::Construct(const FArguments& InArgs)
{
	ImageBrush = InArgs._InImageBrush;
	ShowText = InArgs._InShowText;

	ChildSlot
		[
			SNew(SHorizontalBox)
			+SHorizontalBox::Slot()
			.HAlign(HAlign_Left)
			.VAlign(VAlign_Center)
			[
				SNew(SImage)
				.Image(ImageBrush.Get())
			]
			+SHorizontalBox::Slot()
			.HAlign(HAlign_Left)
			.VAlign(VAlign_Center)
			.Padding(24,0)
			[
				SNew(STextBlock)
				.TextStyle(FGameStyle::Get(),"Text_12")
				.Text(FText::FromString(ShowText.Get()))
			]
		];
}