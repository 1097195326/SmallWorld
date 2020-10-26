#pragma once


#include "NineGridUIController.h"

class MainViewUIController : public NineGridUIController
{
public:
	MainViewUIController();

	virtual void InitControllerView() override; 
	virtual void OnEnter() override;
	virtual void OnExit() override;
	virtual void SelectGameActor(AGameActor * GameActorPtr) override;
	virtual void SelectGameActor(AGameCharacter * GameCharacterPtr)override;

	void	SelectHorde();

protected:
	


};
