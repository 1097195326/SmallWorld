#include "SoldierPawnController.h"
#include "SoldierPawn.h"



void ASoldierPawnController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);

	SoldierPawn = Cast<ASoldierPawn>(InPawn);

	if (SoldierPawn && SoldierPawn->BehaviorTree)
	{
		RunBehaviorTree(SoldierPawn->BehaviorTree);
		//Blackboard->GetKeyID(TEXT(""));
	}
}
void ASoldierPawnController::UnPossess()
{
	Super::UnPossess();

}