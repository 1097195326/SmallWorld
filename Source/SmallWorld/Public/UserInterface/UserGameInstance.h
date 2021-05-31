#pragma once

#include "WrapGameInstance.h"
#include "UserGameInstance.generated.h"


UCLASS()
class UUserGameInstance : public UWrapGameInstance
{
	GENERATED_BODY()
		
private:
	FTimerHandle GameUpdateHandle;

	void UpdateGame();

public:
	UUserGameInstance();

	virtual void On_Init() override;
	virtual void On_Start() override;
	virtual void On_End() override;
	virtual void On_Delete() override;


	virtual bool Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Out = *GLog) override;
	
	virtual    void ApplicationWillEnterBackground() override;
	virtual    void ApplicationHasEnteredForeground() override;
};

#define  User_GameInstance UUserGameInstance::GetInstance()
