#include "SBuildingDetailWidget.h"



void SBuildingDetailWidget::Construct(const FArguments & InArgs)
{

	ChildSlot
		[
			SNew(SVerticalBox)
			+SVerticalBox::Slot()
			.VAlign(VAlign_Bottom)
			.HAlign(HAlign_Center)
			.AutoHeight()
			[
				SNew(SBorder)
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.BorderBackgroundColor(FGameStyle::Get().GetColor("Color.4C6E6F70"))
				.BorderImage(FCoreStyle::Get().GetBrush("GenericWhiteBox"))
				[
					SNew(SHorizontalBox)
				]
			]
			+ SVerticalBox::Slot()
			.VAlign(VAlign_Bottom)
			.HAlign(HAlign_Center)
			.AutoHeight()
			[
				SNew(SBorder)
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.BorderBackgroundColor(FGameStyle::Get().GetColor("Color.4C6E6F70"))
				.BorderImage(FCoreStyle::Get().GetBrush("GenericWhiteBox"))
				[
					SNew(SHorizontalBox)
				]
			]
		];

}