#pragma once
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Seek.generated.h"

UCLASS()
class UBTTask_Seek : public UBTTaskNode
{
	GENERATED_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


};