#include "SGameActorOperation.h"
#include "GameStyle.h"

void SGameActorOperation::Construct(const FArguments & InArgs)
{
	TSharedPtr<SHorizontalBox> OperationBox;

	ChildSlot
	[
		SNew(SBorder)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.BorderBackgroundColor(FGameStyle::Get().GetColor("Color.4C6E6F70"))
		.BorderImage(FCoreStyle::Get().GetBrush("GenericWhiteBox"))
		[
			SAssignNew(OperationBox, SHorizontalBox)
		]
	];
	OperationBox->AddSlot()
		.VAlign(VAlign_Center)
		.HAlign(HAlign_Center)
		.AutoWidth()
		.Padding(12)
		[
			SNew(SButton)
			.ButtonStyle(&FGameStyle::Get().GetWidgetStyle<FButtonStyle>("MainView.Button.Upgrade"))
			.OnClicked(this, &SGameActorOperation::OnUpgradeButtonClicked)
		];
	OperationBox->AddSlot()
		.VAlign(VAlign_Center)
		.HAlign(HAlign_Center)
		.AutoWidth()
		.Padding(12)
		[
			SNew(SButton)
			.ButtonStyle(&FGameStyle::Get().GetWidgetStyle<FButtonStyle>("MainView.Button.Move"))
			.OnClicked(this, &SGameActorOperation::OnMoveButtonClicked)
		];
	OperationBox->AddSlot()
		.VAlign(VAlign_Center)
		.HAlign(HAlign_Center)
		.AutoWidth()
		.Padding(12)
		[
			SNew(SButton)
			.ButtonStyle(&FGameStyle::Get().GetWidgetStyle<FButtonStyle>("MainView.Button.Rotation"))
			.OnClicked(this, &SGameActorOperation::OnRotationButtonClicked)
		];
	OperationBox->AddSlot()
		.VAlign(VAlign_Center)
		.HAlign(HAlign_Center)
		.AutoWidth()
		.Padding(12)
		[
			SNew(SButton)
			.ButtonStyle(&FGameStyle::Get().GetWidgetStyle<FButtonStyle>("MainView.Button.Clear"))
			.OnClicked(this, &SGameActorOperation::OnClearButtonClicked)
		];

}
FReply SGameActorOperation::OnUpgradeButtonClicked()
{
	return FReply::Handled();
}
FReply SGameActorOperation::OnMoveButtonClicked()
{
	return FReply::Handled();
}
FReply SGameActorOperation::OnRotationButtonClicked()
{
	return FReply::Handled();
}
FReply SGameActorOperation::OnClearButtonClicked()
{
	return FReply::Handled();
}