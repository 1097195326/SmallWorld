#include "UserViewportClient.h"
#include "GameManager.h"

UUserViewportClient * UUserViewportClient::Instance = NULL;

void UUserViewportClient::PostInitProperties()
{
	Super::PostInitProperties();
	Instance = this;
}
UUserViewportClient * UUserViewportClient::GetInstance()
{
	return Instance;
}

void UUserViewportClient::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GameManager::GetInstance()->Update(DeltaTime);


}