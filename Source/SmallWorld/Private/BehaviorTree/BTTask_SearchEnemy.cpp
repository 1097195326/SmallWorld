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
	int32 MoveDis = SoldierPawn->GetCurrentWeapon()->GetAttackRange();
	AGroundTileActor* MainTile = SoldierPawn->GetOriginGroundTile();
	TArray<AGroundTileActor*>  AroundTiles;
	TArray<AGroundTileActor*>  EnemyTiles;
	GameManager::GetGroundTileAroundSoldier(MainTile, MoveDis, AroundTiles,true);
	GameManager::GetGroundTilesWithCondition(AroundTiles, EnemyTiles, SoldierPawn, false, true, false);

	TArray<ASoldierPawn*> EnemyArray;
	/*for (AGroundTileActor* IterActor : EnemyTiles)
	{
		if (IterActor->IsHaveGameActor())
		{
			EnemyArray.Append(IterActor->GetGameActors());
		}
	}*/
	ASoldierPawn * BestEnemy = SoldierPawn->GetBestEnemy(EnemyArray);
	if (BestEnemy == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("EnemyActor")), BestEnemy);

	return EBTNodeResult::Succeeded;
}