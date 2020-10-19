#include "LoginViewUIController.h"
#include "GameDataManager.h"
#include "UserController.h"
#include "UserViewportClient.h"
#include "SGameMenuPageWidget.h"


LoginViewUIController::LoginViewUIController()
{
	RaceMenuPage = MakeShareable(new FGameMenuPage());
	RaceMenuPage->AddMenuItem(FText::FromString(TransLanguage("Game_Race_Human")), this, &LoginViewUIController::MenuOperation, 1);
	RaceMenuPage->AddMenuItem(FText::FromString(TransLanguage("Game_Race_Orc")), this, &LoginViewUIController::MenuOperation, 2);
	RaceMenuPage->AddMenuItem(FText::FromString(TransLanguage("Game_Race_Elf")), this, &LoginViewUIController::MenuOperation, 3);
	RaceMenuPage->AddMenuItem(FText::FromString(TransLanguage("Game_Race_Undead")), this, &LoginViewUIController::MenuOperation, 4);

	MainMenuPage = MakeShareable(new FGameMenuPage());
	MainMenuPage->MenuTitle = FText::FromString(TransLanguage("Game_Race"));
	RaceMenuItem = MainMenuPage->AddMenuItem(FText::FromString(TransLanguage("Game_Race")), RaceMenuPage);
	MainMenuPage->AddMenuItem(FText::FromString(TransLanguage("Game_Start")), this, &LoginViewUIController::MenuOperation, 5);

}
void LoginViewUIController::InitControllerView()
{

}
void LoginViewUIController::OnEnter()
{
	MainMenuPage->InitialiseRootMenu(User_Controller, FGameStyle::Get().GetWidgetStyle<FGameMenuStyle>("Menu_MainView"), User_GameClient);

	MainMenuPage->ShowRootMenu();
}
void LoginViewUIController::OnExit()
{
	MainMenuPage->DestroyRootMenu();

}
void LoginViewUIController::MenuOperation(int32 InIndex)
{
	switch (InIndex)
	{
	case 1:
	{
		RaceMenuItem->Text = FText::FromString(TransLanguage("Game_Race_Human"));
		MainMenuPage->RootMenuPageWidget->MenuGoBack();
		break;
	}
	case 2:
	{
		RaceMenuItem->Text = FText::FromString(TransLanguage("Game_Race_Orc"));
		MainMenuPage->RootMenuPageWidget->MenuGoBack();
		break;
	}
	case 3:
	{
		RaceMenuItem->Text = FText::FromString(TransLanguage("Game_Race_Elf"));
		MainMenuPage->RootMenuPageWidget->MenuGoBack();
		break;
	}
	case 4:
	{
		RaceMenuItem->Text = FText::FromString(TransLanguage("Game_Race_Undead"));
		MainMenuPage->RootMenuPageWidget->MenuGoBack();
		break;
	}
	case 5:
		break;
	}
}