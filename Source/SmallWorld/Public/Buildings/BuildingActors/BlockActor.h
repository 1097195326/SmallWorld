#pragma once

#include "BaseBuildingActor.h"
#include "BlockData.h"
#include "BlockActor.generated.h"

class ACityActor;



UCLASS()
class ABlockActor : public ABaseBuildingActor
{
	GENERATED_BODY()
public:
	ABlockActor();
	virtual void		On_Init() override;
    
	FVector				GetFillLocation();
	int					GetFillNum();
    void				FillBuilding(ABaseBuildingActor * _building);
    void				RemoveBuilding(ABaseBuildingActor * _building);

    
	void				SetCity(ACityActor * _City);
	ACityActor *		GetCity();


	virtual bool		IsInWorld() override;

private:
	virtual FString GetMeshPath() override;
    
    
    FString GrassCentreDirtTile;
    FString GrassFullDirtTiles;
    FString GrassTile;
    FString GrassToDirtEdgeTile;
    FString GrassToDirtTile;
    FString DirtTile;

	ACityActor * mCity;

	BlockData * mBlockData;

	TArray<ABaseBuildingActor *>  mFillBuildingActors;

};
