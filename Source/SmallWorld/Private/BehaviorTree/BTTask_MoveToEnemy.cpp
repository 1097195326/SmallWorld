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
	FVector Location = SoldierPawn->GetEnemy()->GetActorLocation();
	return EBTNodeResult::Succeeded;

	if (EPathFollowingRequestResult::RequestSuccessful == SoldierController->MoveToActor(SoldierPawn->GetEnemy(), 5000.f))
	//if (EPathFollowingRequestResult::AlreadyAtGoal == SoldierController->MoveToLocation(Location, 100.f))
	{
		return EBTNodeResult::InProgress;

	}
	return EBTNodeResult::Succeeded;
}
void UBTTask_MoveToEnemy::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{


}