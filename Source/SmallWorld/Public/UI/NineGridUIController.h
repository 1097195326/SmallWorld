#pragma once


#include "UIControllerInterface.h"

class NineGridUIController : public UIControllerInterface
{
public:
	NineGridUIController();

	
	SHorizontalBox::FSlot * GetTopLeftSlot() { return TopLeftSlot; }
	SHorizontalBox::FSlot * GetTopCenterSlot() { return TopCenterSlot; }
	SHorizontalBox::FSlot * GetTopRightSlot() { return TopRightSlot; }

	SHorizontalBox::FSlot * GetMiddleLeftSlot() { return MiddleLeftSlot; }
	SHorizontalBox::FSlot * GetMiddleCenterSlot() { return MiddleCenterSlot; }
	SHorizontalBox::FSlot * GetMiddleRightSlot() { return MiddleRightSlot; }

	SHorizontalBox::FSlot * GetBottomLeftSlot() { return BottomLeftSlot; }
	SHorizontalBox::FSlot * GetBottomCenterSlot() { return BottomCenterSlot; }
	SHorizontalBox::FSlot * GetBottomRightSlot() { return BottomRightSlot; }
protected:

	SHorizontalBox::FSlot * TopLeftSlot = NULL;
	SHorizontalBox::FSlot * TopCenterSlot = NULL;
	SHorizontalBox::FSlot * TopRightSlot = NULL;

	SHorizontalBox::FSlot * MiddleLeftSlot = NULL;
	SHorizontalBox::FSlot * MiddleCenterSlot = NULL;
	SHorizontalBox::FSlot * MiddleRightSlot = NULL;

	SHorizontalBox::FSlot * BottomLeftSlot = NULL;
	SHorizontalBox::FSlot * BottomCenterSlot = NULL;
	SHorizontalBox::FSlot * BottomRightSlot = NULL;
};