#include "BTDecorator_IsSetTargetLocation.h"
#include "SoldierPawnController.h"
#include "SoldierPawn.h"
#include "BehaviorTree/BlackboardComponent.h"



bool UBTDecorator_IsSetTargetLocation::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	ASoldierPawnController * SoldierController = Cast<ASoldierPawnController>(OwnerComp.GetAIOwner());
	if (SoldierController == nullptr)
	{
		return false;
	}
	if (SoldierController->MoveToLocation() != FVector::ZeroVector)
	{
		return true;
	}

	return false;
}