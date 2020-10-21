#include "UserGameInstance.h"
#include "GameManager.h"
#include "TimerManager.h"

#include "UI/SlateStyles/GameStyle.h"
#include "GameDataManager.h"


UUserGameInstance::UUserGameInstance()
{
	
}
void UUserGameInstance::On_Init()
{
	m_Instance = this;
	

	FGameStyle::Startup();

	GameDataManager::GetInstance()->LoadData();

}
void UUserGameInstance::On_Start()
{
	//GetTimerManager().SetTimer(GameUpdateHandle, this, &UUserGameInstance::UpdateGame, 0.1f, true);

}
void UUserGameInstance::On_Delete()
{

}
void UUserGameInstance::UpdateGame()
{

}
void UUserGameInstance::ApplicationWillEnterBackground()
{

}
void UUserGameInstance::ApplicationHasEnteredForeground()
{

}
bool UUserGameInstance::Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Out)
{
	if (Super::Exec(InWorld, Cmd, Out))
	{
		return true;
	}
	
	return false;
}