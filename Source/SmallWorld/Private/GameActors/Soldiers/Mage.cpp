#include "Mage.h"
#include "GameManager.h"
#include "Kismet/KismetMathLibrary.h"
#include "BaseSoldierDataClass.h"
#include "GroundTileActor.h"
#include "CommandCenterDataClass.h"


AMage::AMage()
{
	

}
bool AMage::TryMoveSoldier()
{
	FVector CastleActorLocation = GetSoldierData()->GetCommandCenter()->GetBuildingActor()->GetCastleTileActor()->GetActorLocation();
	int32 MoveDis = GetSoldierData()->GetMoveRange();
	int32 VisibilityDis = GetSoldierData()->GetVisibleRange();
	AGroundTileActor* MainTile = GetOriginGroundTile();
	TArray<AGroundTileActor*>  AroundTiles;
	TArray<AGroundTileActor*>  FarCastleAroundTiles;
	GameManager::GetGroundTileAroundSoldier(MainTile, MoveDis, AroundTiles);
	GameManager::GetGroundTilesFarCastle((FIntVector)CastleActorLocation, MainTile, AroundTiles, FarCastleAroundTiles);
	TArray<TileMapStruct> ArrayTileMap = GameManager::GetGroundTilesNearSoldiers(FarCastleAroundTiles, VisibilityDis, this, false);
	AGroundTileActor * FindTile = GameManager::GetGroundTileWithSoldiersNum(ArrayTileMap);

	AGroundTileActor * ToggleTile = nullptr;
	if (FindTile)
	{
		ToggleTile = FindTile;
	}
	else
	{
		ToggleTile = GameManager::GetGroundTileWithDistance(MainTile, AroundTiles);
	}
	if (ToggleTile)
	{
		TargetGroundTile = ToggleTile;
		OriginGroundTile->SetBusy(true);
		TargetGroundTile->SetBusy(true);
		return true;
	}
	return false;
}