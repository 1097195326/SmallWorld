#include "UserViewportClient.h"
#include "ProgressManager.h"

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

	ProgressManager::GetInstance()->Tick(DeltaTime);

}