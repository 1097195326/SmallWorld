#include "BTTask_SearchEnemy.h"
#include "SoldierPawnController.h"
#include "SoldierPawn.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameManager.h"
#include "BaseSoldierDataClass.h"
#include "GroundTileActor.h"

EBTNodeResult::Type UBTTask_SearchEnemy::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ASoldierPawnController * SoldierController = Cast<ASoldierPawnController>(OwnerComp.GetAIOwner());
	ASoldierPawn * SoldierPawn = Cast<ASoldierPawn>(SoldierController->GetPawn());
	if (SoldierController == nullptr || SoldierPawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	int32 MoveDis = SoldierPawn->GetSoldierData()->GetMovability();
	AGroundTileActor* MainTile = SoldierPawn->GetOriginGroundTile();
	TArray<AGroundTileActor*>  AroundTiles;
	GameManager::GetGroundTileAroundSoldier(MainTile, MoveDis, AroundTiles);

	TArray<ASoldierPawn*> SoldiersArray;
	for (AGroundTileActor* IterActor : AroundTiles)
	{
		if (IterActor->HaveSoldiers())
		{
			SoldiersArray.Append(IterActor->GetSoldiers());
		}
	}
	ASoldierPawn * BestEnemy = SoldierPawn->GetBestEnemy(SoldiersArray);
	OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("EnemyActor")), BestEnemy);


	return EBTNodeResult::Succeeded;
}