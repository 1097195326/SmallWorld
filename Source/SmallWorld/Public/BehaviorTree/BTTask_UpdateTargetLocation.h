#pragma once
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_UpdateTargetLocation.generated.h"

UCLASS()
class UBTTask_UpdateTargetLocation : public UBTTaskNode
{
	GENERATED_BODY()

		virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


};