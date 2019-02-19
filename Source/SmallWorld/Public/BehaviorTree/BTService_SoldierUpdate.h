#pragma once
#include "BehaviorTree/BTService.h"

#include "BTService_SoldierUpdate.generated.h"

UCLASS()
class UBTService_SoldierUpdate : public UBTService
{
	GENERATED_BODY()
public:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};