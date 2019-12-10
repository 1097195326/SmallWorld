#pragma once


#include "NineGridUIController.h"


class MainViewUIController : public NineGridUIController
{
public:

	virtual TSharedPtr<SWidget>		MakeTopLeftWidget() override;
	virtual TSharedPtr<SWidget>		MakeTopCenterWidget() override;
	virtual TSharedPtr<SWidget>		MakeTopRightWidget() override;

	virtual TSharedPtr<SWidget>		MakeMiddleLeftWidget() override;
	virtual TSharedPtr<SWidget>		MakeMiddleCenterWidget() override;
	virtual TSharedPtr<SWidget>		MakeMiddleRightWidget() override;

	virtual TSharedPtr<SWidget>		MakeBottomLeftWidget() override;
	virtual TSharedPtr<SWidget>		MakeBottomCenterWidget() override;
	virtual TSharedPtr<SWidget>		MakeBottomRightWidget() override;

};
