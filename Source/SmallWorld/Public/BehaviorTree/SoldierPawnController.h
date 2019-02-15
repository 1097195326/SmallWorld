#pragma once
#include "AIController.h"

#include "SoldierPawnController.generated.h"

UCLASS()
class ASoldierPawnController : public AAIController
{
	GENERATED_BODY()
public:

	virtual void Possess(APawn* InPawn) override;
	virtual void UnPossess() override;


protected:

private:
	class ASoldierPawn * SoldierPawn;

};