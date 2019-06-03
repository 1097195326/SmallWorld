#include "BTTask_AttackEnemy.h"
#include "SoldierPawnController.h"
#include "SoldierPawn.h"

EBTNodeResult::Type UBTTask_AttackEnemy::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ASoldierPawnController * SoldierController = Cast<ASoldierPawnController>(OwnerComp.GetAIOwner());
	ASoldierPawn * SoldierPawn = Cast<ASoldierPawn>(SoldierController->GetPawn());
	if (SoldierController == nullptr || SoldierPawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::Succeeded;
}