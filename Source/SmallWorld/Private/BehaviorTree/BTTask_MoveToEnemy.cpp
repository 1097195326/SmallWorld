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
	AcceptableRadius = SoldierPawn->GetCurrentWeapon()->GetAttackRange();

	EBTNodeResult::Type ReturnResult = Super::ExecuteTask(OwnerComp, NodeMemory);
	if (ReturnResult == EBTNodeResult::InProgress)
	{
		SoldierPawn->SetSoldierAnimState(SoldierAnimState::Anim_Run);
	}

	return ReturnResult;
}
void UBTTask_MoveToEnemy::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	ASoldierPawnController * SoldierController = Cast<ASoldierPawnController>(OwnerComp.GetAIOwner());
	ASoldierPawn * SoldierPawn = Cast<ASoldierPawn>(SoldierController->GetPawn());
	if (SoldierPawn)
	{
		SoldierPawn->SetSoldierAnimState(SoldierAnimState::Anim_Idle);
	}
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);
}