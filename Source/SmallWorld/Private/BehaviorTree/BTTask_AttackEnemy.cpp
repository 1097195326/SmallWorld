#include "BTTask_AttackEnemy.h"
#include "SoldierPawnController.h"
#include "SoldierPawn.h"
#include "TimerManager.h"


UBTTask_AttackEnemy::UBTTask_AttackEnemy()
{
	SoldierPawn = nullptr;
	IsCallBack = false;
}
EBTNodeResult::Type UBTTask_AttackEnemy::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	
	ASoldierPawnController * SoldierController = Cast<ASoldierPawnController>(OwnerComp.GetAIOwner());
	SoldierPawn = Cast<ASoldierPawn>(SoldierController->GetPawn());
	if (SoldierController == nullptr || SoldierPawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	

	FTimerHandle AttackHandle;
	FTimerHandle AttackPointHandle;
	IsCallBack = false;
	GetWorld()->GetTimerManager().SetTimer(AttackHandle, this, &UBTTask_AttackEnemy::AttackFunc, SoldierPawn->GetCurrentWeapon()->GetAttackInterval());
	GetWorld()->GetTimerManager().SetTimer(AttackPointHandle, this, &UBTTask_AttackEnemy::AttackPointFunc, SoldierPawn->GetCurrentWeapon()->GetAttackPonit());
	
	return EBTNodeResult::InProgress;
}
void UBTTask_AttackEnemy::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	if (IsCallBack)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}

}
void UBTTask_AttackEnemy::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	if (SoldierPawn)
	{

	}
}
void UBTTask_AttackEnemy::AttackFunc()
{
	if (SoldierPawn->IsAlive())
	{
		
	}

	IsCallBack = true;
}
void UBTTask_AttackEnemy::AttackPointFunc()
{
	if (SoldierPawn->IsAlive())
	{
		SoldierPawn->AttackEnemy();
	}
}