#include "SHGameActorIcon.h"
#include "GameStyle.h"



void SHGameActorIcon::Construct(const FArguments& InArgs)
{
	ImageBrush = InArgs._InImageBrush;
	ShowText = InArgs._InShowText;

	ChildSlot
		[
			SNew(SHorizontalBox)
			+SHorizontalBox::Slot()
			.HAlign(HAlign_Left)
			.VAlign(VAlign_Center)
			.AutoWidth()
			[
				SNew(SBox)
				.WidthOverride(InArgs._InImageWidth)
				.HeightOverride(InArgs._InImageHeight)
				[
					SNew(SImage)
					.Image(ImageBrush)
				]
			]
			+SHorizontalBox::Slot()
			.HAlign(HAlign_Left)
			.VAlign(VAlign_Center)
			.AutoWidth()		
			.Padding(24,0)
			[
				SNew(STextBlock)
				.TextStyle(FGameStyle::Get(),"Text_12")
				.Text(FText::FromString(ShowText.Get()))
			]
		];
}