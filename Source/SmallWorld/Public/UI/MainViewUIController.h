#pragma once


#include "NineGridUIController.h"
#include "GameMenuPage.h"

class MainViewUIController : public NineGridUIController
{
public:
	MainViewUIController();

	virtual void InitControllerView() override; 
	virtual void OnEnter() override;
	virtual void OnExit() override;
	virtual void SelectGameActor(AGameActor * GameActorPtr) override;

	void	SelectHorde();

protected:
	TSharedPtr<FGameMenuPage>	MainMenuPage;


};
