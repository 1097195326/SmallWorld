#pragma once


#include "UIControllerInterface.h"

class NineGridUIController : public UIControllerInterface
{
public:
	NineGridUIController();

	
	SVerticalBox::FSlot * GetLeftTopSlot() { return LeftTopSlot; }
	SVerticalBox::FSlot * GetLeftCenterSlot() { return LeftCenterSlot; }
	SVerticalBox::FSlot * GeLeftBottomSlot() { return LeftBottomSlot; }

	SVerticalBox::FSlot * GetMiddleTopSlot() { return MiddleTopSlot; }
	SVerticalBox::FSlot * GetMiddleCenterSlot() { return MiddleCenterSlot; }
	SVerticalBox::FSlot * GetMiddleBottomSlot() { return MiddleBottomSlot; }

	SVerticalBox::FSlot * GetRightTopSlot() { return RightTopSlot; }
	SVerticalBox::FSlot * GetRightCenterSlot() { return RightCenterSlot; }
	SVerticalBox::FSlot * GetRightBottomSlot() { return RightBottomSlot; }
protected:

	SVerticalBox::FSlot * LeftTopSlot = NULL;
	SVerticalBox::FSlot * LeftCenterSlot = NULL;
	SVerticalBox::FSlot * LeftBottomSlot = NULL;

	SVerticalBox::FSlot * MiddleTopSlot = NULL;
	SVerticalBox::FSlot * MiddleCenterSlot = NULL;
	SVerticalBox::FSlot * MiddleBottomSlot = NULL;

	SVerticalBox::FSlot * RightTopSlot = NULL;
	SVerticalBox::FSlot * RightCenterSlot = NULL;
	SVerticalBox::FSlot * RightBottomSlot = NULL;
};