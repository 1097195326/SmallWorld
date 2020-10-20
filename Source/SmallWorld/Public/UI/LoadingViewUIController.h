#pragma once


#include "UIControllerInterface.h"



class LoadingViewUIController : public UIControllerInterface
{
public:
	LoadingViewUIController();

	virtual void InitControllerView() override;
	virtual void OnEnter() override;
	virtual void OnExit() override;

};