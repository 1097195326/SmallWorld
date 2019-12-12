#include "NineGridUIController.h"


NineGridUIController::NineGridUIController()
{
	ControllerType = UIControllerInterface::T_NineGrid;

}
void NineGridUIController::InitControllerView()
{
	ControllerView = SNew(SOverlay)
		+ SOverlay::Slot()
		[
			SNew(SVerticalBox)
			+SVerticalBox::Slot()
			.VAlign(VAlign_Top)
			.HAlign(HAlign_Fill)
			[
				SNew(SHorizontalBox)
				+SHorizontalBox::Slot()
				.VAlign(VAlign_Top)
				.HAlign(HAlign_Left)
				[
					MakeTopLeftWidget().ToSharedRef()
				]
				+ SHorizontalBox::Slot()
				.VAlign(VAlign_Top)
				.HAlign(HAlign_Center)
				[
					MakeTopCenterWidget().ToSharedRef()
				]
				+ SHorizontalBox::Slot()
				.VAlign(VAlign_Top)
				.HAlign(HAlign_Right)
				[
					MakeTopRightWidget().ToSharedRef()
				]
			]
			+ SVerticalBox::Slot()
			.VAlign(VAlign_Fill)
			.HAlign(HAlign_Fill)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.VAlign(VAlign_Center)
				.HAlign(HAlign_Left)
				[
					MakeMiddleLeftWidget().ToSharedRef()
				]
				+ SHorizontalBox::Slot()
				.VAlign(VAlign_Center)
				.HAlign(HAlign_Center)
				[
					MakeMiddleCenterWidget().ToSharedRef()
				]
				+ SHorizontalBox::Slot()
				.VAlign(VAlign_Center)
				.HAlign(HAlign_Right)
				[
					MakeMiddleRightWidget().ToSharedRef()
				]
			]
			+ SVerticalBox::Slot()
			.VAlign(VAlign_Bottom)
			.HAlign(HAlign_Fill)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.VAlign(VAlign_Bottom)
				.HAlign(HAlign_Left)
				[
					MakeBottomLeftWidget().ToSharedRef()
				]
				+ SHorizontalBox::Slot()
				.VAlign(VAlign_Bottom)
				.HAlign(HAlign_Center)
				[
					MakeBottomCenterWidget().ToSharedRef()
				]
				+ SHorizontalBox::Slot()
				.VAlign(VAlign_Bottom)
				.HAlign(HAlign_Right)
				[
					MakeBottomRightWidget().ToSharedRef()
				]
			]
		];

}
TSharedPtr<SWidget> NineGridUIController::MakeTopLeftWidget()
{
	return SNew(SOverlay);
}
TSharedPtr<SWidget>		NineGridUIController::MakeTopCenterWidget()
{
	return SNew(SOverlay);
}
TSharedPtr<SWidget>		NineGridUIController::MakeTopRightWidget()
{
	return SNew(SOverlay);
}

TSharedPtr<SWidget>		NineGridUIController::MakeMiddleLeftWidget()
{
	return SNew(SOverlay);
}
TSharedPtr<SWidget>		NineGridUIController::MakeMiddleCenterWidget()
{
	return SNew(SOverlay);
}
TSharedPtr<SWidget>		NineGridUIController::MakeMiddleRightWidget()
{
	return SNew(SOverlay);
}

TSharedPtr<SWidget>		NineGridUIController::MakeBottomLeftWidget()
{
	return SNew(SOverlay);
}
TSharedPtr<SWidget>		NineGridUIController::MakeBottomCenterWidget()
{
	return SNew(SOverlay);
}
TSharedPtr<SWidget>		NineGridUIController::MakeBottomRightWidget()
{
	return SNew(SOverlay);
}
void NineGridUIController::Enter()
{
	InitControllerView();
	GVC->AddViewportWidgetContent(ControllerView.ToSharedRef());
}
void NineGridUIController::Exit()
{
	if (ControllerView.IsValid())
	{
		GVC->RemoveViewportWidgetContent(ControllerView.ToSharedRef());
	}
}