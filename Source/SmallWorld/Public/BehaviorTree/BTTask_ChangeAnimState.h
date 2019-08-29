#pragma once
#include "BehaviorTree/BTTaskNode.h"
#include "SoldierPawn.h"

#include "BTTask_ChangeAnimState.generated.h"

UCLASS()
class UBTTask_ChangeAnimState : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_ChangeAnimState();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere)
		TEnumAsByte<SoldierAnimState>  ToAnimState;
};