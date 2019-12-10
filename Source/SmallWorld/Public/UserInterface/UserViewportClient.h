#pragma once


#include "Engine/GameViewportClient.h"

#include "UserViewportClient.generated.h"

UCLASS()
class UUserViewportClient : public UGameViewportClient
{
public:
	GENERATED_BODY()
		
	virtual void PostInitProperties() override;

	static UUserViewportClient * GetInstance();
private:
	static UUserViewportClient * UserViewportClientInstance;
};
#define  GVC  UUserViewportClient::GetInstance()