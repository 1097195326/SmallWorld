#pragma once
#include "GameFramework/FloatingPawnMovement.h"

#include "SoldierPawnMovement.generated.h"

UCLASS()
class USoldierPawnMovement :public UFloatingPawnMovement
{
	GENERATED_BODY()
public:
	
	virtual void InitializeComponent() override;
	virtual void ApplyControlInputToVelocity(float DeltaTime) override;

protected:

private:
	class ASoldierPawn * SoldierPawn;
	class ASoldierPawnController * SoldierController;

};