#include "BTTask_AttackEnemy.h"
#include "SoldierPawnController.h"
#include "SoldierPawn.h"
#include "TimerManager.h"


UBTTask_AttackEnemy::UBTTask_AttackEnemy()
{
	
	SoldierPawn = nullptr;

}
EBTNodeResult::Type UBTTask_AttackEnemy::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	
	ASoldierPawnController * SoldierController = Cast<ASoldierPawnController>(OwnerComp.GetAIOwner());
	SoldierPawn = Cast<ASoldierPawn>(SoldierController->GetPawn());
	if (SoldierController == nullptr || SoldierPawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	

	SoldierPawn->SetSoldierAnimState(Anim_Attack1);

	FTimerHandle AttackHandle;
	FTimerHandle AttackPointHandle;

	GetWorld()->GetTimerManager().SetTimer(AttackHandle, this, &UBTTask_AttackEnemy::AttackFunc, SoldierPawn->GetCurrentWeapon()->GetAttackInterval());
	GetWorld()->GetTimerManager().SetTimer(AttackPointHandle, this, &UBTTask_AttackEnemy::AttackPointFunc, SoldierPawn->GetCurrentWeapon()->GetAttackPonit());
	
	return EBTNodeResult::Succeeded;
}
void UBTTask_AttackEnemy::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

}
void UBTTask_AttackEnemy::OnMessage(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, FName Message, int32 RequestID, bool bSuccess)
{
	Super::OnMessage(OwnerComp, NodeMemory, Message, RequestID, bSuccess);

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