#include "UserGameInstance.h"
#include "GameManager.h"
#include "TimerManager.h"



UUserGameInstance::UUserGameInstance()
{
	
}
void UUserGameInstance::On_Init()
{
	m_Instance = this;
	

}
void UUserGameInstance::On_Start()
{
	GameManager::GetInstance()->StartGame();
	
	//GetTimerManager().SetTimer(GameUpdateHandle, this, &UUserGameInstance::UpdateGame, 0.1f, true);

}
void UUserGameInstance::On_End()
{
	GameManager::GetInstance()->EndGame();
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