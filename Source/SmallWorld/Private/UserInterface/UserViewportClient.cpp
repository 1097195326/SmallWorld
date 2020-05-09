#include "UserViewportClient.h"
#include "ProgressManager.h"

UUserViewportClient * UUserViewportClient::UserViewportClientInstance = NULL;

void UUserViewportClient::PostInitProperties()
{
	Super::PostInitProperties();
	UserViewportClientInstance = this;
}
UUserViewportClient * UUserViewportClient::GetInstance()
{
	return UserViewportClientInstance;
}

void UUserViewportClient::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ProgressManager::GetInstance()->Tick(DeltaTime);

}