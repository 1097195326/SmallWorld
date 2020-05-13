#include "SHorizontalItemOperation.h"
#include "GameStyle.h"
#include "GameTools.h"

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
				SNew(SBox)
				.WidthOverride(150)
				.HeightOverride(40)
				.Visibility(EVisibility::Collapsed)
				[
					SNew(SSlider)
					.Style(&FGameStyle::Get().GetWidgetStyle<FSliderStyle>("Slider"))
					.Value(0)
					.OnValueChanged(this, &SHorizontalItemOperation::OnValueChange)
				]
			]
			+ SHorizontalBox::Slot()
				.VAlign(VAlign_Center)
				.HAlign(HAlign_Left)
				.AutoWidth()
				.Padding(24, 0)
				[
					SNew(SEditableTextBox)
					.HintText(FText::FromString("10"))
					.OnTextChanged(this,&SHorizontalItemOperation::OnTextChange)
				]
			+SHorizontalBox::Slot()
			.VAlign(VAlign_Center)
			.HAlign(HAlign_Left)
			.AutoWidth()
			.Padding(24, 0)
			[
				SNew(SBox)
				.WidthOverride(40)
				.HeightOverride(40)
				[
					SNew(SButton)
					.ButtonStyle(&FGameStyle::Get().GetWidgetStyle<FButtonStyle>("CommonButton"))
					.Text(FText::FromString(ButtonShowText.Get()))
				]
			]

		];
}
void SHorizontalItemOperation::OnValueChange(float InValue)
{

}
void SHorizontalItemOperation::OnTextChange(const FText& InText)
{
	FString InStr = InText.ToString();
	if (GameTools::IsNumber(InStr))
	{

	}
	else if (InStr.IsNumeric())
	{
		int32 InputNum = FCString::Atoi(*InStr);
	}

}