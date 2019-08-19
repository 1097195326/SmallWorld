#include "BTTask_ChangeState.h"
#include "SoldierPawnController.h"


UBTTask_ChangeState::UBTTask_ChangeState()
{
	mToState = SoldierState::S_Normal;
}
EBTNodeResult::Type UBTTask_ChangeState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ASoldierPawnController * SoldierController = Cast<ASoldierPawnController>(OwnerComp.GetAIOwner());
	ASoldierPawn * SoldierPawn = Cast<ASoldierPawn>(SoldierController->GetPawn());
	if (SoldierController == nullptr || SoldierPawn == nullptr)
	{
	    return EBTNodeResult::Failed;
	}
	
	SoldierPawn->ChangeSoldierState(mToState);
	SoldierPawn->SetSoldierAnimState(Anim_Idle);

	return EBTNodeResult::Succeeded;
}