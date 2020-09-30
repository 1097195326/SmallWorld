#include "NineGridUIController.h"


NineGridUIController::NineGridUIController()
{
	ControllerType = UIControllerInterface::T_NineGrid;

	ControllerView = SNew(SOverlay);

	ControllerView->AddSlot(1)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(0)
		.Expose(LowOverlaySlot)
		[
			SNew(SOverlay)
			+ SOverlay::Slot()
			.VAlign(VAlign_Top)
			.HAlign(HAlign_Left)
			.Expose(LeftTopSlot)
			+ SOverlay::Slot()
			.VAlign(VAlign_Center)
			.HAlign(HAlign_Left)
			.Expose(LeftCenterSlot)
			+ SOverlay::Slot()
			.VAlign(VAlign_Bottom)
			.HAlign(HAlign_Left)
			.Expose(LeftBottomSlot)
			+ SOverlay::Slot()
			.VAlign(VAlign_Top)
			.HAlign(HAlign_Center)
			.Expose(MiddleTopSlot)
			+ SOverlay::Slot()
			.VAlign(VAlign_Center)
			.HAlign(HAlign_Center)
			.Expose(MiddleCenterSlot)
			+ SOverlay::Slot()
			.VAlign(VAlign_Bottom)
			.HAlign(HAlign_Center)
			.Expose(MiddleBottomSlot)
			+ SOverlay::Slot()
			.VAlign(VAlign_Top)
			.HAlign(HAlign_Right)
			.Expose(RightTopSlot)
			+ SOverlay::Slot()
			.VAlign(VAlign_Center)
			.HAlign(HAlign_Right)
			.Expose(RightCenterSlot)
			+ SOverlay::Slot()
			.VAlign(VAlign_Bottom)
			.HAlign(HAlign_Right)
			.Expose(RightBottomSlot)
		];
}