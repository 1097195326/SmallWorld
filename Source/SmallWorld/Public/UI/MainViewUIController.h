#pragma once


#include "NineGridUIController.h"


class MainViewUIController : public NineGridUIController
{
public:
	TSharedPtr<SWidget>	 TestWidget();
	
	virtual void InitControllerView();

	void	ShowBuildingWidget();


	FReply OnPowerClicked();
	FReply OnHeroClicked();
	FReply OnMapClicked();
	FReply OnMenuClicked();

protected:
	TSharedPtr<SWidget> CreateUserView();
	TSharedPtr<SWidget>	CreateToWorldButton();
	TSharedPtr<SWidget>	CreateBuildingButton();




};
