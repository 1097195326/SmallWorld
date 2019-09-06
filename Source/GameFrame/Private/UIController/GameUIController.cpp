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
			[
				LeftBottomCornerView.ToSharedRef()
			];
		RootView->AddSlot()
			.VAlign(VAlign_Top)
			.HAlign(HAlign_Left)
			[
				LeftTopCornerView.ToSharedRef()
			];
		RootView->AddSlot()
			.VAlign(VAlign_Bottom)
			.HAlign(HAlign_Right)
			[
				RightBottomCornerView.ToSharedRef()
			];
		RootView->AddSlot()
			.VAlign(VAlign_Top)
			.HAlign(HAlign_Right)
			[
				RightTopCornerView.ToSharedRef()
			];
		RootView->AddSlot()
			.VAlign(VAlign_Center)
			.HAlign(HAlign_Left)
			[
				LeftView.ToSharedRef()
			];
		RootView->AddSlot()
			.VAlign(VAlign_Center)
			.HAlign(HAlign_Right)
			[
				RightView.ToSharedRef()
			];
		RootView->AddSlot()
			.VAlign(VAlign_Bottom)
			.HAlign(HAlign_Center)
			[
				BottomView.ToSharedRef()
			];
		RootView->AddSlot()
			.VAlign(VAlign_Top)
			.HAlign(HAlign_Center)
			[
				TopView.ToSharedRef()
			];
		RootView->AddSlot()
			.VAlign(VAlign_Center)
			.HAlign(HAlign_Center)
			[
				CenterView.ToSharedRef()
			];
		
		
}