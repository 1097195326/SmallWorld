#include "GameUIController.h"

GameUIController::GameUIController()
{
	LeftView = nullptr;
	RightView = nullptr;
	TopView = nullptr;
	BottomView = nullptr;
	
	CenterView = nullptr;

	LeftBottomCornerView = nullptr;
	LeftTopCornerView = nullptr;
	RightTopCornerView = nullptr;
	RightBottomCornerView = nullptr;
}
void GameUIController::InitView()
{
	
	CreateCenterView();

	CreateLeftView();
	CreateRightView();
	CreateTopView();
	CreateBottomView();

	CreateLeftTopCornerView();
	CreateLeftBottomCornerView();
	CreateRightBottomCornerView();
	CreateRightTopCornerView();

	SAssignNew(RootView, SOverlay);

	RootView->AddSlot()
		.VAlign(VAlign_Bottom)
		.HAlign(HAlign_Left)
		.Expose(LeftBottomCornerViewSlot)
		[
			LeftBottomCornerView.ToSharedRef()
		];
	RootView->AddSlot()
		.VAlign(VAlign_Top)
		.HAlign(HAlign_Left)
		.Expose(LeftTopCornerViewSlot)
		[
			LeftTopCornerView.ToSharedRef()
		];
	RootView->AddSlot()
		.VAlign(VAlign_Bottom)
		.HAlign(HAlign_Right)
		.Expose(RightBottomCornerViewSlot)
		[
			RightBottomCornerView.ToSharedRef()
		];
	RootView->AddSlot()
		.VAlign(VAlign_Top)
		.HAlign(HAlign_Right)
		.Expose(RightTopCornerViewSlot)
		[
			RightTopCornerView.ToSharedRef()
		];
	RootView->AddSlot()
		.VAlign(VAlign_Center)
		.HAlign(HAlign_Left)
		.Expose(LeftViewSlot)
		[
			LeftView.ToSharedRef()
		];
	RootView->AddSlot()
		.VAlign(VAlign_Center)
		.HAlign(HAlign_Right)
		.Expose(RightViewSlot)
		[
			RightView.ToSharedRef()
		];
	RootView->AddSlot()
		.VAlign(VAlign_Bottom)
		.HAlign(HAlign_Center)
		.Expose(BottomViewSlot)
		[
			BottomView.ToSharedRef()
		];
	RootView->AddSlot()
		.VAlign(VAlign_Top)
		.HAlign(HAlign_Center)
		.Expose(TopViewSlot)
		[
			TopView.ToSharedRef()
		];
	RootView->AddSlot()
		.VAlign(VAlign_Center)
		.HAlign(HAlign_Center)
		.Expose(CenterViewSlot)
		[
			CenterView.ToSharedRef()
		];
		
	
}