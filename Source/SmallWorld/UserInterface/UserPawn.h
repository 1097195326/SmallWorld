#pragma once
#include "GamePawn.h"
#include "UserPawn.generated.h"

UCLASS()
class AUserPawn : public AGamePawn
{
	GENERATED_BODY()
public:
	virtual void On_Init() override;
	virtual void On_Start() override;
	virtual void On_Tick(float delta) override;
	virtual void On_Delete() override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

};

