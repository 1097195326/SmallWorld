#include "BTTask_ChangeState.h"
#include "SoldierPawnController.h"


UBTTask_ChangeState::UBTTask_ChangeState()
{
	ToState = SoldierState::S_Idle;
}
EBTNodeResult::Type UBTTask_ChangeState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ASoldierPawnController * SoldierController = Cast<ASoldierPawnController>(OwnerComp.GetAIOwner());
	ASoldierPawn * SoldierPawn = Cast<ASoldierPawn>(SoldierController->GetPawn());
	if (SoldierController == nullptr || SoldierPawn == nullptr)
	{
	    return EBTNodeResult::Failed;
	}
	
	SoldierPawn->ChangeSoldierState(ToState);

	return EBTNodeResult::Succeeded;
}