#include "SmallWorldInstance.h"
#include "GameWorld.h"
#include "TimerManager.h"

#include "UI/SlateStyles/GameStyle.h"
#include "GameDataManager.h"

USmallWorldInstance::USmallWorldInstance()
{
	

}
void USmallWorldInstance::On_Init()
{
	m_Instance = this;
	FGameStyle::Startup();

	GameDataManager::GetInstance()->LoadData();

}
void USmallWorldInstance::On_Start()
{
	GetTimerManager().SetTimer(GameUpdateHandle, this, &USmallWorldInstance::UpdateGame, 0.1f, true);

}
void USmallWorldInstance::On_Delete()
{

}
void USmallWorldInstance::UpdateGame()
{
	GameWorld::GetInstance()->Update();

}
void USmallWorldInstance::ApplicationWillEnterBackground()
{

}
void USmallWorldInstance::ApplicationHasEnteredForeground()
{

}