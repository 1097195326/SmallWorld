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
	
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

	

};