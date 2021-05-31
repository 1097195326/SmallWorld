#pragma once


#include "NineGridUIController.h"

class MainViewUIController : public NineGridUIController
{
public:
	MainViewUIController();

	virtual void InitControllerView() override; 
	virtual void OnEnter() override;
	virtual void OnExit() override;
	virtual void SelectGameActor(AWrapActor * GameActorPtr) override;
	virtual void SelectGameActor(AWrapCharacter * GameCharacterPtr)override;

	void	SelectHorde();

protected:
	


};
