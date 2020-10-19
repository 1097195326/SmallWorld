#pragma once
#include "UIControllerInterface.h"
#include "GameMenuPage.h"


class LoginViewUIController : public UIControllerInterface
{
public:
	LoginViewUIController();

	virtual void InitControllerView() override;
	virtual void OnEnter() override;
	virtual void OnExit() override;
protected:
	void  MenuOperation(int32 InIndex);
	TSharedPtr<FGameMenuItem>	RaceMenuItem;
	TSharedPtr<FGameMenuPage>	RaceMenuPage;

	TSharedPtr<FGameMenuPage>	MainMenuPage;
};