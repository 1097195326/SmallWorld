#include "BTTask_OffsetPursuit.h"
#include "SoldierPawnController.h"
#include "SoldierPawn.h"
#include "BehaviorTree/BlackboardComponent.h"



EBTNodeResult::Type UBTTask_OffsetPursuit::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ASoldierPawnController * SoldierController = Cast<ASoldierPawnController>(OwnerComp.GetAIOwner());
	

	return EBTNodeResult::Failed;
}