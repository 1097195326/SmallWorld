#pragma once
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_MoveToForward.generated.h"

UCLASS()
class UBTTask_MoveToForward : public UBTTaskNode
{
	GENERATED_BODY()

		virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


};