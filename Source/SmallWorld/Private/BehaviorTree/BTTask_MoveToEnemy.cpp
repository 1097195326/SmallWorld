#include "BTTask_MoveToEnemy.h"
#include "SoldierPawnController.h"
#include "SoldierPawn.h"

EBTNodeResult::Type UBTTask_MoveToEnemy::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ASoldierPawnController * SoldierController = Cast<ASoldierPawnController>(OwnerComp.GetAIOwner());
	ASoldierPawn * SoldierPawn = Cast<ASoldierPawn>(SoldierController->GetPawn());
	if (SoldierController == nullptr || SoldierPawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	
	if (EPathFollowingRequestResult::AlreadyAtGoal ==SoldierController->MoveToActor(SoldierPawn->GetEnemy()),SoldierPawn->GetFieldOfAttack())
	{
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::InProgress;
}