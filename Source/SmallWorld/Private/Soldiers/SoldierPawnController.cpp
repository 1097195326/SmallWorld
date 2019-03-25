#include "SoldierPawnController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "SoldierPawn.h"

ASoldierPawnController::ASoldierPawnController(const FObjectInitializer& ObjectInitializer /* = FObjectInitializer::Get() */)
{
	

}
void ASoldierPawnController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);

	ASoldierPawn * SoldierPawn = Cast<ASoldierPawn>(InPawn);

	// start behavior
	if (SoldierPawn && SoldierPawn->BehaviorTree)
	{
		RunBehaviorTree(SoldierPawn->BehaviorTree);
	}

}
void ASoldierPawnController::UnPossess()
{
	Super::UnPossess();
	if (BrainComponent)
	{
		Cast<UBehaviorTreeComponent>(BrainComponent)->StopTree();
	}

}
