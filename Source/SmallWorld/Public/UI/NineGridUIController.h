#pragma once


#include "UIControllerInterface.h"

class NineGridUIController : public UIControllerInterface
{
public:
	NineGridUIController();

	virtual void			InitControllerView();
	virtual void			Enter();
	virtual void			Exit();

	virtual TSharedPtr<SWidget>		MakeTopLeftWidget();
	virtual TSharedPtr<SWidget>		MakeTopCenterWidget();
	virtual TSharedPtr<SWidget>		MakeTopRightWidget();

	virtual TSharedPtr<SWidget>		MakeMiddleLeftWidget();
	virtual TSharedPtr<SWidget>		MakeMiddleCenterWidget();
	virtual TSharedPtr<SWidget>		MakeMiddleRightWidget();

	virtual TSharedPtr<SWidget>		MakeBottomLeftWidget();
	virtual TSharedPtr<SWidget>		MakeBottomCenterWidget();
	virtual TSharedPtr<SWidget>		MakeBottomRightWidget();

};