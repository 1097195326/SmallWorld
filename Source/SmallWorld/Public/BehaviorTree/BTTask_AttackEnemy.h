#pragma once
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_AttackEnemy.generated.h"

UCLASS()
class UBTTask_AttackEnemy : public UBTTaskNode
{
	GENERATED_BODY()

		virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


};