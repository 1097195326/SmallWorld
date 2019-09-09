#pragma once

#include "UIController.h"
#include "SWidget.h"
#include "SBox.h"
#include "SOverlay.h"

class GAMEFRAME_API GameUIController : public UIController
{
public:
	GameUIController();

	virtual void InitView() override;

	
protected:
	virtual TSharedPtr<SBox>			CreateLeftView() { return nullptr; }
	virtual TSharedPtr<SBox>			CreateRightView() { return nullptr; }
	virtual TSharedPtr<SBox>			CreateTopView() { return nullptr; }
	virtual TSharedPtr<SBox>			CreateBottomView() { return nullptr; }

	virtual TSharedPtr<SBox>			CreateCenterView() { return nullptr; }

	virtual TSharedPtr<SBox>			CreateLeftBottomCornerView() { return nullptr; }
	virtual TSharedPtr<SBox>			CreateLeftTopCornerView() { return nullptr; }
	virtual TSharedPtr<SBox>			CreateRightTopCornerView() { return nullptr; }
	virtual TSharedPtr<SBox>			CreateRightBottomCornerView() { return nullptr; }


	TSharedPtr<SOverlay>			RootView;

	TSharedPtr<SBox>			LeftView;
	SOverlay::FOverlaySlot *	LeftViewSlot;

	TSharedPtr<SBox>			RightView;
	SOverlay::FOverlaySlot *	RightViewSlot;

	TSharedPtr<SBox>			TopView;
	SOverlay::FOverlaySlot *	TopViewSlot;

	TSharedPtr<SBox>			BottomView;
	SOverlay::FOverlaySlot *	BottomViewSlot;

	TSharedPtr<SBox>			CenterView;
	SOverlay::FOverlaySlot *	CenterViewSlot;

	TSharedPtr<SBox>			LeftBottomCornerView;
	SOverlay::FOverlaySlot *	LeftBottomCornerViewSlot;


	TSharedPtr<SBox>			LeftTopCornerView;
	SOverlay::FOverlaySlot *	LeftTopCornerViewSlot;

	TSharedPtr<SBox>			RightTopCornerView;
	SOverlay::FOverlaySlot *	RightTopCornerViewSlot;

	TSharedPtr<SBox>			RightBottomCornerView;
	SOverlay::FOverlaySlot *	RightBottomCornerViewSlot;

};