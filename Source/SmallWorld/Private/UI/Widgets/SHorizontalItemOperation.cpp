#include "SHorizontalItemOperation.h"


void SHorizontalItemOperation::Construct(const FArguments & InArgs)
{
	ShowText = InArgs._InShowText;
	ButtonShowText = InArgs._InButtonText;

	ChildSlot
		[
			SNew(SHorizontalBox)
			+SHorizontalBox::Slot()
			.VAlign(VAlign_Center)
			.HAlign(HAlign_Left)
.AutoWidth()
			[
				SNew(STextBlock)
				.TextStyle(FGameStyle::Get(),"Text_12")
				.Text(ShowText.Get())
			]
			+ SHorizontalBox::Slot()
			.VAlign(VAlign_Center)
			.HAlign(HAlign_Left)
				.AutoWidth()
				.Padding(24, 0)
			[
				SNew(SSlider)
				.OnValueChanged(this,&SHorizontalItemOperation::OnValueChange)
			]
			+SHorizontalBox::Slot()
			.VAlign(VAlign_Center)
			.HAlign(HAlign_Left)
				.AutoWidth()
				.Padding(24, 0)
			[
				SNew(SButton)
				.ButtonStyle(&FGameStyle::Get().GetWidgetStyle<FButtonStyle>(""))
				.Text(FText::FromString(ButtonShowText.Get()))
			]

		];
}
void SHorizontalItemOperation::OnValueChange(float InValue)
{

}