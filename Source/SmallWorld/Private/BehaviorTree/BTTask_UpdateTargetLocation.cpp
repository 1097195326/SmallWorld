#include "BTTask_UpdateTargetLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "SoldierPawnController.h"
#include "SoldierPawn.h"

EBTNodeResult::Type UBTTask_UpdateTargetLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ASoldierPawnController * SoldierController = Cast<ASoldierPawnController>(OwnerComp.GetAIOwner());
	ASoldierPawn * SoldierPawn = Cast<ASoldierPawn>(SoldierController->GetPawn());
	if (SoldierController == nullptr || SoldierPawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	FVector MoveLocation = SoldierPawn->GetMoveLocation();
	const FVector TargetLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(FName(TEXT("TargetLocation")));
	if (TargetLocation == MoveLocation)
	{
		return EBTNodeResult::Failed;
	}
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName(TEXT("TargetLocation")), MoveLocation);

	return EBTNodeResult::Succeeded;
}