#pragma once
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_SearchEnemy.generated.h"

UCLASS()
class UBTTask_SearchEnemy : public UBTTaskNode
{
	GENERATED_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


};