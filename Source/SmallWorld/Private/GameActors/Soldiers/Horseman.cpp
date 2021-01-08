#include "Horseman.h"
#include "GameManager.h"
#include "Kismet/KismetMathLibrary.h"
#include "BaseSoldierDataClass.h"
#include "GroundTileActor.h"

AHorseman::AHorseman()
{
	

}
bool AHorseman::TryMoveSoldier()
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