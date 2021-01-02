#include "BTTask_UpdateTargetLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "SoldierPawnController.h"
#include "SoldierPawn.h"
#include "GroundTileActor.h"

EBTNodeResult::Type UBTTask_UpdateTargetLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ASoldierPawnController * SoldierController = Cast<ASoldierPawnController>(OwnerComp.GetAIOwner());
	ASoldierPawn * SoldierPawn = Cast<ASoldierPawn>(SoldierController->GetPawn());
	if (SoldierController == nullptr || SoldierPawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	AGroundTileActor * TargetGroundActor = SoldierPawn->GetTargetGroundTile();
	if (TargetGroundActor)
	{
		FVector MoveLocation = TargetGroundActor->GetActorLocation();
		const FVector TargetLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(FName(TEXT("TargetLocation")));
		if (TargetLocation == MoveLocation)
		{
			return EBTNodeResult::Failed;
		}
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName(TEXT("TargetLocation")), MoveLocation);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}