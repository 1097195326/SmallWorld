#include "SBuildingDetailOperation.h"

void SBuildingDetailOperation::Construct(const FArguments & InArgs)
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
			.OnClicked(this, &SBuildingDetailOperation::OnUpgradeButtonClicked)
		];
	OperationBox->AddSlot()
		.VAlign(VAlign_Center)
		.HAlign(HAlign_Center)
		.AutoWidth()
		.Padding(12)
		[
			SNew(SButton)
			.ButtonStyle(&FGameStyle::Get().GetWidgetStyle<FButtonStyle>("MainView.Button.Move"))
			.OnClicked(this, &SBuildingDetailOperation::OnMoveButtonClicked)
		];
	OperationBox->AddSlot()
		.VAlign(VAlign_Center)
		.HAlign(HAlign_Center)
		.AutoWidth()
		.Padding(12)
		[
			SNew(SButton)
			.ButtonStyle(&FGameStyle::Get().GetWidgetStyle<FButtonStyle>("MainView.Button.Rotation"))
			.OnClicked(this, &SBuildingDetailOperation::OnRotationButtonClicked)
		];
	OperationBox->AddSlot()
		.VAlign(VAlign_Center)
		.HAlign(HAlign_Center)
		.AutoWidth()
		.Padding(12)
		[
			SNew(SButton)
			.ButtonStyle(&FGameStyle::Get().GetWidgetStyle<FButtonStyle>("MainView.Button.Clear"))
			.OnClicked(this, &SBuildingDetailOperation::OnClearButtonClicked)
		];

}
FReply SBuildingDetailOperation::OnUpgradeButtonClicked()
{
	return FReply::Handled();
}
FReply SBuildingDetailOperation::OnMoveButtonClicked()
{
	return FReply::Handled();
}
FReply SBuildingDetailOperation::OnRotationButtonClicked()
{
	return FReply::Handled();
}
FReply SBuildingDetailOperation::OnClearButtonClicked()
{
	return FReply::Handled();
}