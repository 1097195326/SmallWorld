#pragma once
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_MoveToEnemy.generated.h"

UCLASS()
class UBTTask_MoveToEnemy : public UBTTaskNode
{
	GENERATED_BODY()
public:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};