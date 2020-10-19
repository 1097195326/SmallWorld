#pragma once
#include "UIControllerInterface.h"
#include "GameMenuPage.h"


class LoginUIController : public UIControllerInterface
{
public:
	LoginUIController();

	virtual void InitControllerView() override;
	virtual void OnEnter() override;
	virtual void OnExit() override;
protected:
	void  MenuOperation(int32 InIndex);
	TSharedPtr<FGameMenuItem>	RaceMenuItem;
	TSharedPtr<FGameMenuPage>	RaceMenuPage;

	TSharedPtr<FGameMenuPage>	MainMenuPage;
};