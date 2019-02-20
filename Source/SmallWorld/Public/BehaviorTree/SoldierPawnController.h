#pragma once
#include "AIController.h"

#include "SoldierPawnController.generated.h"

class UBehaviorTreeComponent;
class UBlackboardComponent;

UCLASS()
class ASoldierPawnController : public AAIController
{
	GENERATED_BODY()
public:
	ASoldierPawnController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	virtual void Possess(APawn* InPawn) override;
	virtual void UnPossess() override;

	/*UPROPERTY(transient)
		UBlackboardComponent* BlackboardComp;
	UPROPERTY(transient)
		UBehaviorTreeComponent* BehaviorComp;*/
protected:

public:
	UPROPERTY(VisibleAnywhere)
	class ASoldierPawn * SoldierPawn;

	void	AddSteeringForce(FVector Force);
	FVector	SteeringForce();
	void	SetCurrentLocation(FVector Location);
	FVector	CurrentLocation();
	
private:
	FVector vSteeringForce;
	FVector	vCurrentLocation;
};