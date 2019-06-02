#pragma once
#include "BehaviorTree/BTTaskNode.h"

#include "BTTask_ToGroupForward.generated.h"


UCLASS()
class UBTTask_ToGroupForward : public UBTTaskNode
{
	GENERATED_BODY()
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};