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
	AGroundTileActor* MainTile = GetOriginGroundTile();
	TArray<AGroundTileActor*>  AroundTiles;
	GameManager::GetGroundTileAroundSoldier(MainTile, MoveDis, AroundTiles);
	if (AroundTiles.Num() > 0)
	{
		int32 TileIndex = UKismetMathLibrary::RandomInteger(AroundTiles.Num());
		AGroundTileActor * TileActor = AroundTiles[TileIndex];
		TargetGroundTile = TileActor;
		OriginGroundTile->SetBusy(true);
		TargetGroundTile->SetBusy(true);
		return true;
	}
	return false;
}