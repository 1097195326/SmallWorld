#include "BTTask_ToIdle.h"
#include "SoldierPawnController.h"
#include "SoldierPawn.h"


UBTTask_ToIdle::UBTTask_ToIdle()
{

}
EBTNodeResult::Type UBTTask_ToIdle::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ASoldierPawnController * SoldierController = Cast<ASoldierPawnController>(OwnerComp.GetAIOwner());
	ASoldierPawn * SoldierPawn = Cast<ASoldierPawn>(SoldierController->GetPawn());
	if (SoldierController == nullptr || SoldierPawn == nullptr)
	{
	    return EBTNodeResult::Failed;
	}
	
	SoldierPawn->ChangeSoldierState(SoldierState::S_Idle);
	SoldierPawn->SetSoldierAnimState(Anim_Idle);

	return EBTNodeResult::Succeeded;
}