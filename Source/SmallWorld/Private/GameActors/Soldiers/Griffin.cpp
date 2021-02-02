#include "Griffin.h"
#include "GameManager.h"
#include "Kismet/KismetMathLibrary.h"
#include "BaseSoldierDataClass.h"
#include "GroundTileActor.h"
#include "CommandCenterDataClass.h"

AGriffin::AGriffin()
{
	

}
bool AGriffin::TryMoveSoldier()
{
	FVector CastleActorLocation = GetSoldierData()->GetCommandCenter()->GetBuildingActor()->GetCastleTileActor()->GetActorLocation();
	int32 MoveDis = GetSoldierData()->GetMoveRange();
	int32 VisibilityDis = GetSoldierData()->GetVisibleRange();
	AGroundTileActor* MainTile = GetOriginGroundTile();
	TArray<AGroundTileActor*>  AroundTiles;
	TArray<AGroundTileActor*>  FarCastleAroundTiles;
	GameManager::GetGroundTileAroundSoldier(MainTile, MoveDis, AroundTiles, true);
	GameManager::GetGroundTilesFarCastle((FIntVector)CastleActorLocation, MainTile, AroundTiles, FarCastleAroundTiles);
	TArray<AGroundTileActor*> HaveSoldierTiles;
	GameManager::GetGroundTilesWithCondition(FarCastleAroundTiles, HaveSoldierTiles, this,true,false,false);
	TArray<TileMapStruct> ArrayTileMap = GameManager::GetGroundTilesNearSoldiers(HaveSoldierTiles, VisibilityDis, this, false);
	AGroundTileActor * FindTile = GameManager::GetGroundTileWithSoldiersNum(ArrayTileMap);

	AGroundTileActor * ToggleTile = nullptr;
	if (ToggleTile == nullptr)
	{
		ToggleTile = FindTile;
	}
	if (ToggleTile == nullptr)
	{
		ToggleTile = GameManager::GetGroundTileWithDistance(MainTile, HaveSoldierTiles);
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