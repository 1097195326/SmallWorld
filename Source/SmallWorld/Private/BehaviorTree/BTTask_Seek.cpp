#include "BTTask_Seek.h"
#include "SoldierPawnController.h"
#include "SoldierPawn.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTask_Seek::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ASoldierPawnController * SoldierController = Cast<ASoldierPawnController>(OwnerComp.GetAIOwner());
	ASoldierPawn * SoldierPawn = SoldierController->SoldierPawn;

	/*if (!SoldierController->IsArrive())
	{
		SoldierController->ArriveOn();
	}*/
	if (!SoldierController->IsSeek())
	{
		SoldierController->SeekOn();
	}
	return EBTNodeResult::Succeeded;
}