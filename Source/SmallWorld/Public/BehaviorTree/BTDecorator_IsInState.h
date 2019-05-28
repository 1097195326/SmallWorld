#pragma once

#include "BehaviorTree/BTDecorator.h"
#include "SoldierPawn.h"
#include "BTDecorator_IsInState.generated.h"

UCLASS()
class UBTDecorator_IsInState : public UBTDecorator
{
	GENERATED_BODY()
public:
	UBTDecorator_IsInState();
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	UPROPERTY(EditAnywhere)
		SoldierState  mIsInState;

};