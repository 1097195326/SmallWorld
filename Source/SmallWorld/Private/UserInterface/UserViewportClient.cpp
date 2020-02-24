#include "UserViewportClient.h"



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


}
bool UUserViewportClient::HavePriviewActor()
{
	return PriviewActor.IsValid();
}
void UUserViewportClient::UpdatePriviewActor(FString IconName /* = TEXT("") */)
{
	if (!IconName.IsEmpty())
	{
		DestroyPriviewActor();
		GetGameInstance()->GetFirstLocalPlayerController();
	}
	


}
void UUserViewportClient::DropPriviewActor()
{

}
void UUserViewportClient::DestroyPriviewActor()
{
	if (PriviewActor.IsValid())
	{
		PriviewActor->BeginDestroy();
	}
	PriviewActor.Reset();
}