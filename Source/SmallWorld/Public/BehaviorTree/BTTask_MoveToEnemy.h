#pragma once
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_MoveToEnemy.generated.h"

UCLASS()
class UBTTask_MoveToEnemy : public UBTTaskNode
{
	GENERATED_BODY()

		virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


};