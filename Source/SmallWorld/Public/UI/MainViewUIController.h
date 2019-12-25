#pragma once


#include "NineGridUIController.h"


class MainViewUIController : public NineGridUIController
{
public:
	TSharedPtr<SWidget>	 TestWidget();
	
	virtual void InitControllerView();
protected:
	TSharedPtr<SWidget> CreateUserView();
	TSharedPtr<SWidget>	CreateToWorldButton();
	TSharedPtr<SWidget>	CreateBuildingButton();

};
