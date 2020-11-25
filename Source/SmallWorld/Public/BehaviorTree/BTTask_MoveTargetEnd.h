#pragma once
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_MoveTargetEnd.generated.h"

UCLASS()
class UBTTask_MoveTargetEnd : public UBTTaskNode
{
	GENERATED_BODY()

		virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


};