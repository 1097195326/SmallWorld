#pragma once
#include "GameController.h"
#include "UserController.generated.h"

UCLASS()
class AUserController : public AGameController
{
	GENERATED_BODY()

public:
	virtual void On_Init() override;
	virtual void On_Start() override;
	virtual void On_Tick(float delta) override;
	virtual void On_Delete() override;

};

