#pragma once
#include "BehaviorTree/BTTaskNode.h"

#include "BTTask_ToIdle.generated.h"

UCLASS()
class UBTTask_ToIdle : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_ToIdle();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};