#pragma once
#include "BehaviorTree/Tasks/BTTask_MoveTo.h"
#include "BTTask_MoveToEnemy.generated.h"

UCLASS()
class UBTTask_MoveToEnemy : public UBTTask_MoveTo
{
	GENERATED_BODY()
public:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;

};