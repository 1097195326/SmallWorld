#pragma once
#include "BehaviorTree/BTService.h"
#include "SoldierPawn.h"
#include "BTService_SoldierUpdate.generated.h"

UCLASS()
class UBTService_SoldierUpdate : public UBTService
{
	GENERATED_BODY()
public:
	UBTService_SoldierUpdate();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	SoldierState preSoldierState;

};