#include "BTTask_AttackEnemy.h"
#include "SoldierPawnController.h"
#include "SoldierPawn.h"
#include "TimerManager.h"


UBTTask_AttackEnemy::UBTTask_AttackEnemy()
{
	IsActive = false;
	SoldierPawn = nullptr;

}
EBTNodeResult::Type UBTTask_AttackEnemy::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (IsActive)
	{
		return EBTNodeResult::InProgress;
	}
	ASoldierPawnController * SoldierController = Cast<ASoldierPawnController>(OwnerComp.GetAIOwner());
	SoldierPawn = Cast<ASoldierPawn>(SoldierController->GetPawn());
	if (SoldierController == nullptr || SoldierPawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	IsActive = true;

	SoldierPawn->SetSoldierAnimState(Anim_Attack1);

	FTimerHandle AttackHandle;
	FTimerHandle AttackPointHandle;

	GetWorld()->GetTimerManager().SetTimer(AttackHandle, this, &UBTTask_AttackEnemy::AttackFunc, SoldierPawn->GetCurrentWeapon()->GetAttackInterval());
	GetWorld()->GetTimerManager().SetTimer(AttackPointHandle, this, &UBTTask_AttackEnemy::AttackPointFunc, SoldierPawn->GetCurrentWeapon()->GetAttackPonit());

	return EBTNodeResult::Succeeded;
}
void UBTTask_AttackEnemy::AttackFunc()
{
	if (SoldierPawn->IsAlive())
	{
		SoldierPawn->SetSoldierAnimState(Anim_Idle);
	}
	IsActive = false;
}
void UBTTask_AttackEnemy::AttackPointFunc()
{
	if (SoldierPawn->IsAlive())
	{
		SoldierPawn->AttackEnemy();
	}
}