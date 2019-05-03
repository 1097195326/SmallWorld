#pragma once

#include "BaseBuildingActor.h"
#include "BlockData.h"
#include "BlockActor.generated.h"

class ACityActor;



UCLASS()
class ABlockActor : public ABaseBuildingActor
{
	GENERATED_BODY()

private:
	BlockTitleType mTitleType;
	CityOrientation mCityOrientation;
    
	ACityActor * mCity;
    
	BlockData * mBlockData;
    
    TArray<ABaseBuildingActor *>  mFillBuildingActors;
    
public:
	ABlockActor();
	virtual void On_Init() override;
    
    
    void FillBuilding(ABaseBuildingActor * _building);
    void RemoveBuilding(ABaseBuildingActor * _building);

	BlockTitleType GetTileType();

	void SetOrientation(CityOrientation _orientation);
	CityOrientation GetOrientation();
    
	void SetCity(ACityActor * _City);
	ACityActor * GetCity();


	virtual bool IsInWorld() override;

private:
	virtual FString GetMeshPath() override;
    
    
    FString GrassCentreDirtTile;
    FString GrassFullDirtTiles;
    FString GrassTile;
    FString GrassToDirtEdgeTile;
    FString GrassToDirtTile;
    FString DirtTile;
};
