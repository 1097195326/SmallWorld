#pragma once

#include "GAppInstance.h"

#include "SmallWorldInstance.generated.h"

UCLASS()
class USmallWorldInstance : public UGAppInstance
{
	GENERATED_BODY()
		
public:
	USmallWorldInstance();

	virtual void On_Init() override;
	virtual void On_Start() override;
	virtual void On_Delete() override;

	virtual    void ApplicationWillEnterBackground() override;
	virtual    void ApplicationHasEnteredForeground() override;
};