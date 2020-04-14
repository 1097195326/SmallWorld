#include "SBuildingDetailWidget.h"

void SBuildingDetailWidget::Construct(const FArguments & InArgs)
{
	bNeedOperation = InArgs._NeedOperation;

	SGameActorDetailWidget::Construct(SGameActorDetailWidget::FArguments()
	.ActorName(InArgs._ActorName)
	.ActorLevel(InArgs._ActorLevel)
	.ActorHealth(InArgs._ActorHealth)
	.DetailWidget(InArgs._DetailWidget));

	if (bNeedOperation)
	{
		TSharedPtr<SHorizontalBox> OperationBox;
		BottomSlot->AttachWidget
		(
			SNew(SBorder)
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.BorderBackgroundColor(FGameStyle::Get().GetColor("Color.4C6E6F70"))
			.BorderImage(FCoreStyle::Get().GetBrush("GenericWhiteBox"))
			[
				SAssignNew(OperationBox, SHorizontalBox)
			]
		);
		OperationBox->AddSlot()
			.VAlign(VAlign_Center)
			.HAlign(HAlign_Center)
			.AutoWidth()
			.Padding(12)
			[
				SNew(SButton)
				.ButtonStyle(&FGameStyle::Get().GetWidgetStyle<FButtonStyle>("MainView.Button.Upgrade"))
				.OnClicked(this, &SBuildingDetailWidget::OnUpgradeButtonClicked)
			];
		OperationBox->AddSlot()
			.VAlign(VAlign_Center)
			.HAlign(HAlign_Center)
			.AutoWidth()
			.Padding(12)
			[
				SNew(SButton)
				.ButtonStyle(&FGameStyle::Get().GetWidgetStyle<FButtonStyle>("MainView.Button.Move"))
				.OnClicked(this, &SBuildingDetailWidget::OnMoveButtonClicked)
			];
		OperationBox->AddSlot()
			.VAlign(VAlign_Center)
			.HAlign(HAlign_Center)
			.AutoWidth()
			.Padding(12)
			[
				SNew(SButton)
				.ButtonStyle(&FGameStyle::Get().GetWidgetStyle<FButtonStyle>("MainView.Button.Roation"))
				.OnClicked(this, &SBuildingDetailWidget::OnRotationButtonClicked)
			];
		OperationBox->AddSlot()
			.VAlign(VAlign_Center)
			.HAlign(HAlign_Center)
			.AutoWidth()
			.Padding(12)
			[
				SNew(SButton)
				.ButtonStyle(&FGameStyle::Get().GetWidgetStyle<FButtonStyle>("MainView.Button.Clear"))
				.OnClicked(this, &SBuildingDetailWidget::OnClearButtonClicked)
			];
	}
}
FReply SBuildingDetailWidget::OnUpgradeButtonClicked()
{
	return FReply::Handled();
}
FReply SBuildingDetailWidget::OnMoveButtonClicked()
{
	return FReply::Handled();
}
FReply SBuildingDetailWidget::OnRotationButtonClicked()
{
	return FReply::Handled();
}
FReply SBuildingDetailWidget::OnClearButtonClicked()
{
	return FReply::Handled();
}