#include "BTTask_ChangeAnimState.h"
#include "SoldierPawnController.h"


UBTTask_ChangeAnimState::UBTTask_ChangeAnimState()
{
	ToAnimState = SoldierAnimState::Anim_Idle;
}
EBTNodeResult::Type UBTTask_ChangeAnimState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ASoldierPawnController * SoldierController = Cast<ASoldierPawnController>(OwnerComp.GetAIOwner());
	ASoldierPawn * SoldierPawn = Cast<ASoldierPawn>(SoldierController->GetPawn());
	if (SoldierController == nullptr || SoldierPawn == nullptr)
	{
	    return EBTNodeResult::Failed;
	}
	
	SoldierPawn->SetSoldierAnimState(ToAnimState);

	return EBTNodeResult::Succeeded;
}