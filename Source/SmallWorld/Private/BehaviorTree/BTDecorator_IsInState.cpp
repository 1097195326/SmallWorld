#include "BTDecorator_IsInState.h"
#include "SoldierPawnController.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTDecorator_IsInState::UBTDecorator_IsInState()
{
	mIsInState = SoldierState::S_Normal;

}
bool UBTDecorator_IsInState::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp,NodeMemory);

	ASoldierPawnController * SoldierController = Cast<ASoldierPawnController>(OwnerComp.GetAIOwner());
	ASoldierPawn * SoldierPawn = Cast<ASoldierPawn>(SoldierController->GetPawn());
	if (SoldierController == nullptr || SoldierPawn == nullptr || mIsInState == SoldierState::S_Normal)
	{
		return false;
	}
	if (SoldierPawn->IsInState(mIsInState))
	{
		return true;
	}

	return false;
}