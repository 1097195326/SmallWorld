#include "SoldierPawnController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "SoldierPawn.h"

ASoldierPawnController::ASoldierPawnController(const FObjectInitializer& ObjectInitializer /* = FObjectInitializer::Get() */)
{
	
	UE_LOG(LogTemp, Log, TEXT("zhx : ASoldierPawnController::ASoldierPawnController"));
	
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("PerceptionComponent");

	PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ASoldierPawnController::OnSightEnemy);
	

}
void ASoldierPawnController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ASoldierPawn * SoldierPawn = Cast<ASoldierPawn>(InPawn);

	PerceptionComponent->ConfigureSense(*SoldierPawn->Sightonfig);
	// start behavior
	if (SoldierPawn && SoldierPawn->GetBehaviorTree())
	{
		RunBehaviorTree(SoldierPawn->GetBehaviorTree());
	}

}
void ASoldierPawnController::OnUnPossess()
{
	Super::OnUnPossess();
	if (BrainComponent)
	{
		Cast<UBehaviorTreeComponent>(BrainComponent)->StopTree();
	}

}
void  ASoldierPawnController::OnSightEnemy(AActor* Actor, FAIStimulus Stimulus)
{

}