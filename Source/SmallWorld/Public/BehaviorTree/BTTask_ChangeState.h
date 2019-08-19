#pragma once
#include "BehaviorTree/BTTaskNode.h"
#include "SoldierPawn.h"

#include "BTTask_ChangeState.generated.h"

UCLASS()
class UBTTask_ChangeState : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_ChangeState();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere)
		SoldierState  mToState;
};