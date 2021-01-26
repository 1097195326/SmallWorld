#include "Archer.h"
#include "GameManager.h"
#include "Kismet/KismetMathLibrary.h"
#include "BaseSoldierDataClass.h"
#include "GroundTileActor.h"

AArcher::AArcher()
{
	CurrentWeapon = ProjectileWeaponClass = NewObject<USoldierProjectileWeapon>();
	ProjectileWeaponClass->SetOwner(this);
	ProjectileWeaponClass->AddToRoot();
}
AArcher::~AArcher()
{
	ProjectileWeaponClass->RemoveFromRoot();
	ProjectileWeaponClass = nullptr;
}
void AArcher::On_Start() 
{
	ProjectileWeaponClass->InitWithWeaponInfo(ProjectileWeaponInfo);

}
bool AArcher::TryMoveSoldier()
{
	int32 MoveDis = GetSoldierData()->GetMoveRange();
	int32 VisibilityDis = GetSoldierData()->GetVisibleRange();
	AGroundTileActor* MainTile = GetOriginGroundTile();
	TArray<AGroundTileActor*>  AroundTiles;
	GameManager::GetGroundTileAroundSoldier(MainTile, MoveDis, AroundTiles);
	TArray<TileMapStruct> ArrayTileMap = GameManager::GetGroundTilesNearSoldiers(AroundTiles, VisibilityDis, this, false);
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