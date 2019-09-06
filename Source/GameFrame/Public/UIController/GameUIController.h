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

	virtual TSharedPtr<SBox>			CreateLeftView() { return nullptr; }
	virtual TSharedPtr<SBox>			CreateRightView() { return nullptr; }
	virtual TSharedPtr<SBox>			CreateTopView() { return nullptr; }
	virtual TSharedPtr<SBox>			CreateBottomView() { return nullptr; }

	virtual TSharedPtr<SBox>			CreateCenterView() { return nullptr; }

	virtual TSharedPtr<SBox>			CreateLeftBottomCornerView() { return nullptr; }
	virtual TSharedPtr<SBox>			CreateLeftTopCornerView() { return nullptr; }
	virtual TSharedPtr<SBox>			CreateRightTopCornerView(){ return nullptr; }
	virtual TSharedPtr<SBox>			CreateRightBottomCornerView(){ return nullptr; }
protected:
	TSharedPtr<SOverlay>			RootView;

	TSharedPtr<SBox>			LeftView;
	TSharedPtr<SBox>			RightView;
	TSharedPtr<SBox>			TopView;
	TSharedPtr<SBox>			BottomView;

	TSharedPtr<SBox>			CenterView;

	TSharedPtr<SBox>			LeftBottomCornerView;
	TSharedPtr<SBox>			LeftTopCornerView;
	TSharedPtr<SBox>			RightTopCornerView;
	TSharedPtr<SBox>			RightBottomCornerView;

};