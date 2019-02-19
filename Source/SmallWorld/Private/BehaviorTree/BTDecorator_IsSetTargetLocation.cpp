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
	ASoldierPawn * SoldierPawn = SoldierController->SoldierPawn;
	if (SoldierPawn)
	{
		return false;
	}
	if (SoldierController->CurrentLocation().SizeSquared() > 0.f)
	{
		return true;
	}

	return true;
}