#pragma once

#include "GAppInstance.h"
#include "SmallWorldInstance.generated.h"


UCLASS()
class USmallWorldInstance : public UGAppInstance
{
	GENERATED_BODY()
		
private:
	FTimerHandle GameUpdateHandle;

	void UpdateGame();

public:
	USmallWorldInstance();

	virtual void On_Init() override;
	virtual void On_Start() override;
	virtual void On_Delete() override;


	virtual bool Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Out = *GLog) override;
	
	virtual    void ApplicationWillEnterBackground() override;
	virtual    void ApplicationHasEnteredForeground() override;
};

#define  User_GameInstance USmallWorldInstance::GetInstance()
