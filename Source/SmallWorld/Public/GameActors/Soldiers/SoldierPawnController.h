#pragma once
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"

#include "SoldierPawnController.generated.h"

class UBehaviorTreeComponent;
class UBlackboardComponent;


UCLASS()
class ASoldierPawnController : public AAIController
{
	GENERATED_BODY()
public:
	ASoldierPawnController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

	virtual void ActorsPerceptionUpdated(const TArray<AActor*>& UpdatedActors) override;
	virtual void Tick(float DeltaTime) override;

};