#include "SmallWorldInstance.h"
#include "GameWorld.h"


USmallWorldInstance::USmallWorldInstance()
{
	

}
void USmallWorldInstance::On_Init()
{
	m_Instance = this;
	GameWorld::GetInstance()->InitWithGameInstance(this);
}
void USmallWorldInstance::On_Start()
{
	

}
void USmallWorldInstance::On_Delete()
{

}
void USmallWorldInstance::ApplicationWillEnterBackground()
{

}
void USmallWorldInstance::ApplicationHasEnteredForeground()
{

}