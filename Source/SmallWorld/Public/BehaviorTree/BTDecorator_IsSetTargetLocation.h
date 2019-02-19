#pragma once

#include "BehaviorTree/BTDecorator.h"

#include "BTDecorator_IsSetTargetLocation.generated.h"

UCLASS()
class UBTDecorator_IsSetTargetLocation : public UBTDecorator
{
	GENERATED_BODY()
public:

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

};