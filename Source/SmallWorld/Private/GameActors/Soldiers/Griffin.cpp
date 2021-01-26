#include "Griffin.h"
#include "GameManager.h"
#include "Kismet/KismetMathLibrary.h"
#include "BaseSoldierDataClass.h"
#include "GroundTileActor.h"

AGriffin::AGriffin()
{
	

}
bool AGriffin::TryMoveSoldier()
{
	int32 MoveDis = GetSoldierData()->GetMoveRange();
	int32 VisibilityDis = GetSoldierData()->GetVisibleRange();
	AGroundTileActor* MainTile = GetOriginGroundTile();
	TArray<AGroundTileActor*>  AroundTiles;
	GameManager::GetGroundTileAroundSoldier(MainTile, MoveDis, AroundTiles,true);
	TArray<AGroundTileActor*> HaveSoldierTiles;
	GameManager::GetGroundTilesWithCondition(AroundTiles, HaveSoldierTiles, this,true,false,true);
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