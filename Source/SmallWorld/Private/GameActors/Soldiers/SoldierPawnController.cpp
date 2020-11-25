#include "SoldierPawnController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "CastleTileActor.h"
#include "GroundTileActor.h"
#include "SoldierPawn.h"
#include "GameConfig.h"
#include "GameDataManager.h"
#include "GameManager.h"


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
void ASoldierPawnController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	

}
void ASoldierPawnController::ActorsPerceptionUpdated(const TArray<AActor *>& UpdatedActors)
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
		ASoldierPawn * bestEnemy = Cast<ASoldierPawn>(UpdatedActors[0]);
		if (bestEnemy)
		{
			SoldierPawn->SetEnemy(bestEnemy);
			SoldierPawn->ChangeSoldierState(SoldierState::S_Fight);
		}
		
	}
}
void ASoldierPawnController::TryMoveSoldier(class ASoldierPawn * InSoldier)
{
	if (InSoldier == nullptr) { return; }
	
	int32 MoveDis = InSoldier->GetSoldierData()->GetMovability();
	AGroundTileActor* MainTile = InSoldier->GetOriginGroundTile();
	TArray<AGroundTileActor*>  AroundTiles;
	GameManager::GetGroundTileAroundSoldier(MainTile, MoveDis, AroundTiles);
	if (AroundTiles.Num() > 0)
	{
		int32 TileIndex = UKismetMathLibrary::RandomInteger(AroundTiles.Num());
		AGroundTileActor * TileActor = AroundTiles[TileIndex];
		InSoldier->SetTargetGroundTile(TileActor);
		InSoldier->SetMoveLocation(TileActor->GetActorLocation());
	}


}