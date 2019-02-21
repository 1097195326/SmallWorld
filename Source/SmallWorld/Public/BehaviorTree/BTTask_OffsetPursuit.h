#pragma once
#include "BehaviorTree/BTTaskNode.h"

#include "BTTask_OffsetPursuit.generated.h"


UCLASS()
class UBTTask_OffsetPursuit : public UBTTaskNode
{
	GENERATED_BODY()
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};