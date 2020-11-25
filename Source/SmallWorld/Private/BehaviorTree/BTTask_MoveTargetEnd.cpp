#include "BTTask_MoveTargetEnd.h"
#include "SoldierPawnController.h"
#include "SoldierPawn.h"
#include "BaseSoldierDataClass.h"

EBTNodeResult::Type UBTTask_MoveTargetEnd::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ASoldierPawnController * SoldierController = Cast<ASoldierPawnController>(OwnerComp.GetAIOwner());
	ASoldierPawn * SoldierPawn = Cast<ASoldierPawn>(SoldierController->GetPawn());
	
	if (SoldierPawn->GetSoldierData()->IsUserData())
	{
		SoldierPawn->MoveToTargetEnd();
	}
	
	return EBTNodeResult::Succeeded;
}