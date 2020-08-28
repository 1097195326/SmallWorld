#pragma once


#include "NineGridUIController.h"


class MainViewUIController : public NineGridUIController
{
public:
	TSharedPtr<SWidget>	 TestWidget();
	
	virtual void InitControllerView() override; 
	virtual void OnEnter() override;
	virtual void OnExit() override;
	virtual void SelectGameActor(AGameActor * GameActorPtr) override;


	FReply OnPowerClicked();
	FReply OnHeroClicked();
	FReply OnMapClicked();
	FReply OnMenuClicked();

protected:
	TSharedPtr<SWidget> CreateUserView();
	TSharedPtr<SWidget>	CreateToWorldButton();
	TSharedPtr<SWidget>	CreateBuildingButton();
	TSharedPtr<SWidget> CreateShowBuildingsWidget();
	TSharedPtr<SWidget> CreateHordeList();



};
