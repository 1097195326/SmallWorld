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

public:
	class ASoldierPawn * SoldierPawn;

	void	AddSteeringForce(FVector Force);
	FVector	SteeringForce();
	void	SetCurrentLocation(FVector Location);
	FVector	CurrentLocation();
	
private:
	FVector vSteeringForce;
	FVector	vCurrentLocation;
};