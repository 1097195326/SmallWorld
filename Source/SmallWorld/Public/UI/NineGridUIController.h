#pragma once


#include "UIControllerInterface.h"

class NineGridUIController : public UIControllerInterface
{
public:
	NineGridUIController();

	SOverlay::FOverlaySlot * GetLeftTopSlot() { return LeftTopSlot; }
	SOverlay::FOverlaySlot * GetLeftCenterSlot() { return LeftCenterSlot; }
	SOverlay::FOverlaySlot * GeLeftBottomSlot() { return LeftBottomSlot; }

	SOverlay::FOverlaySlot * GetMiddleTopSlot() { return MiddleTopSlot; }
	SOverlay::FOverlaySlot * GetMiddleCenterSlot() { return MiddleCenterSlot; }
	SOverlay::FOverlaySlot * GetMiddleBottomSlot() { return MiddleBottomSlot; }

	SOverlay::FOverlaySlot * GetRightTopSlot() { return RightTopSlot; }
	SOverlay::FOverlaySlot * GetRightCenterSlot() { return RightCenterSlot; }
	SOverlay::FOverlaySlot * GetRightBottomSlot() { return RightBottomSlot; }

	/*SVerticalBox::FSlot * GetLeftTopSlot() { return LeftTopSlot; }
	SVerticalBox::FSlot * GetLeftCenterSlot() { return LeftCenterSlot; }
	SVerticalBox::FSlot * GeLeftBottomSlot() { return LeftBottomSlot; }

	SVerticalBox::FSlot * GetMiddleTopSlot() { return MiddleTopSlot; }
	SVerticalBox::FSlot * GetMiddleCenterSlot() { return MiddleCenterSlot; }
	SVerticalBox::FSlot * GetMiddleBottomSlot() { return MiddleBottomSlot; }

	SVerticalBox::FSlot * GetRightTopSlot() { return RightTopSlot; }
	SVerticalBox::FSlot * GetRightCenterSlot() { return RightCenterSlot; }
	SVerticalBox::FSlot * GetRightBottomSlot() { return RightBottomSlot; }*/
protected:

	SOverlay::FOverlaySlot * LeftTopSlot = NULL;
	SOverlay::FOverlaySlot * LeftCenterSlot = NULL;
	SOverlay::FOverlaySlot * LeftBottomSlot = NULL;

	SOverlay::FOverlaySlot * MiddleTopSlot = NULL;
	SOverlay::FOverlaySlot * MiddleCenterSlot = NULL;
	SOverlay::FOverlaySlot * MiddleBottomSlot = NULL;

	SOverlay::FOverlaySlot * RightTopSlot = NULL;
	SOverlay::FOverlaySlot * RightCenterSlot = NULL;
	SOverlay::FOverlaySlot * RightBottomSlot = NULL;

	/*SVerticalBox::FSlot * LeftTopSlot = NULL;
	SVerticalBox::FSlot * LeftCenterSlot = NULL;
	SVerticalBox::FSlot * LeftBottomSlot = NULL;

	SVerticalBox::FSlot * MiddleTopSlot = NULL;
	SVerticalBox::FSlot * MiddleCenterSlot = NULL;
	SVerticalBox::FSlot * MiddleBottomSlot = NULL;

	SVerticalBox::FSlot * RightTopSlot = NULL;
	SVerticalBox::FSlot * RightCenterSlot = NULL;
	SVerticalBox::FSlot * RightBottomSlot = NULL;*/

	SOverlay::FOverlaySlot * LowOverlaySlot = NULL;

};