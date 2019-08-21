#include "SoldierPawnController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "SoldierPawn.h"

ASoldierPawnController::ASoldierPawnController(const FObjectInitializer& ObjectInitializer /* = FObjectInitializer::Get() */)
{
	
	UE_LOG(LogTemp, Log, TEXT("zhx : ASoldierPawnController::ASoldierPawnController"));
	
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("PerceptionComponent");
	

}
void ASoldierPawnController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ASoldierPawn * SoldierPawn = Cast<ASoldierPawn>(InPawn);
	for (auto senseConfig : SoldierPawn->SenseConfigs)
	{
		PerceptionComponent->ConfigureSense(*senseConfig);
	}
	PerceptionComponent->ReregisterComponent();
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
static bool IsOpen = true;

void  ASoldierPawnController::ActorsPerceptionUpdated(const TArray<AActor *>& UpdatedActors)
{
	ASoldierPawn * SoldierPawn = Cast<ASoldierPawn>(GetPawn());
	if (!SoldierPawn )
	{
		return;
	}
	if (SoldierPawn->IsHaveEnemy())
	{

	}
	else
	{
		//ASoldierPawn * bestEnemy = SoldierPawn->GetBestEnemy(UpdatedActors);
		AActor * bestEnemy = Cast<AActor>(UpdatedActors[0]);
		if (bestEnemy && IsOpen)
		{
			//IsOpen = false;
			//SoldierPawn->SetEnemy(bestEnemy);
			MoveToActor(bestEnemy, 100.f);
		}
		
	}
}