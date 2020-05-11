#include "SHordePowerWidget.h"
#include "GameStyle.h"


void SHordePowerWidget::Construct(const FArguments& InArgs)
{
	ChildSlot
		[
			SAssignNew(VerticalBox,SVerticalBox)
			+ SVerticalBox::Slot()
			.HAlign(HAlign_Left)
			.VAlign(VAlign_Top)
			.AutoHeight()
			.Padding(0, 0, 0, 0)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.HAlign(HAlign_Left)
				.VAlign(VAlign_Center)
				.AutoWidth()
				[
					SNew(SBox)
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Center)
					.WidthOverride(128)
					.HeightOverride(128)
					[
						SNew(SButton)
						.ButtonStyle(&FGameStyle::Get().GetWidgetStyle<FButtonStyle>("MainView.Button.Power"))
						.OnClicked(InArgs._OnPowerClicked)
					]
				]
			]
		];
	
	if (true)
	{
		VerticalBox->AddSlot()
		.HAlign(HAlign_Left)
		.VAlign(VAlign_Top)
		.AutoHeight()
		.Padding(0, 0, 0, 0)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.HAlign(HAlign_Left)
			.VAlign(VAlign_Center)
			.AutoWidth()
			[
				SNew(SBox)
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Center)
				.WidthOverride(128)
				.HeightOverride(128)
				[
					SNew(SButton)
					.ButtonStyle(&FGameStyle::Get().GetWidgetStyle<FButtonStyle>("MainView.Button.Hero"))
					.OnClicked(InArgs._OnHeroClicked)
				]
			]
		];
	}
	
}
