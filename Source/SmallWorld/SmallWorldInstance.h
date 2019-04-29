#pragma once

#include "GAppInstance.h"

#include "SmallWorldInstance.generated.h"

#define  SWI USmallWorldInstance::GetInstance()

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

	

	virtual    void ApplicationWillEnterBackground() override;
	virtual    void ApplicationHasEnteredForeground() override;
};