#pragma once
#include "BehaviorTree/BTTaskNode.h"

#include "BTTask_Arrive.generated.h"

UCLASS()
class UBTTask_Arrive : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_Arrive();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere)
		float DecelerationTweaker;
};