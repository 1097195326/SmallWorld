#include "Knight.h"
#include "GameManager.h"
#include "Kismet/KismetMathLibrary.h"
#include "BaseSoldierDataClass.h"
#include "GroundTileActor.h"

AKnight::AKnight()
{
	
	CurrentWeapon = InstantWeaponClass = NewObject<USoldierInstantWeapon>();
	InstantWeaponClass->SetOwner(this);
	InstantWeaponClass->AddToRoot();
	
}
AKnight::~AKnight()
{
	InstantWeaponClass->RemoveFromRoot();
	InstantWeaponClass = nullptr;
}
void AKnight::On_Start()
{
	
	InstantWeaponClass->InitWithWeaponInfo(InstantWeaponInfo);

}
bool AKnight::TryMoveSoldier()
{
	int32 MoveDis = GetSoldierData()->GetMoveRange();
	int32 VisibilityDis = GetSoldierData()->GetVisibleRange();
	AGroundTileActor* MainTile = GetOriginGroundTile();
	TArray<AGroundTileActor*>  AroundTiles;
	GameManager::GetGroundTileAroundSoldier(MainTile, MoveDis, AroundTiles);
	TArray<TileMapStruct> ArrayTileMap = GameManager::GetGroundTilesNearSoldiers(AroundTiles, VisibilityDis, this, true);
	AGroundTileActor * FindTile = GameManager::GetGroundTileWithSoldiersNum(ArrayTileMap, false);

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