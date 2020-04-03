#pragma once


#include "Engine/GameViewportClient.h"

#include "UserViewportClient.generated.h"

UCLASS()
class UUserViewportClient : public UGameViewportClient
{
public:
	GENERATED_BODY()
		
	virtual void PostInitProperties() override;
	virtual void Tick(float DeltaTime) override;

	bool	HavePriviewActor();
	void	UpdatePriviewActor(FVector2D ScreenPosition, FString IconName = TEXT(""));
	void	DropPriviewActor();
	void	DestroyPriviewActor();

	static UUserViewportClient * GetInstance();
private:
	static UUserViewportClient * UserViewportClientInstance;

	class APreviewActor *  PreviewActor;

};
#define  GVC  UUserViewportClient::GetInstance()