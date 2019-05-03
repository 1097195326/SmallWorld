#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ConstructorHelpers.h"
#include "Engine/StaticMesh.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/MeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SmallWorldInstance.h"
#include <vector>
#include <list>
#include "BaseBuildingData.h"
#include "BaseBuildingActor.generated.h"

using namespace std;


const int  BoundSize = 0;
const int  WorldSize = 1;
const int	CitySize = 15;
const int  CastleControllSize = 11;
const int  CastleSize = 7;
const int	CastleCenterSize = 3;
const float TitleSize = 2500.f;
const float WallSize = 625.f;

class ABlockActor;

UCLASS()
class ABaseBuildingActor : public AActor
{
	GENERATED_BODY()
protected:
    BaseBuildingData * mData;
    
    // Need To Save
        // position
        // Rotator
    // End
    int                    mMaxLevel;
    
    
	FString  MeshPathLevel_0;
	FString  MeshPathLevel_1;
	FString  MeshPathLevel_2;
	FString  MeshPathLevel_3;
	FString  MeshPathLevel_4;
	FString  MeshPathLevel_5;

    // protected function
    
	virtual FString GetMeshPath();
    
    ABlockActor * mOnBlockActor;

public:
	ABaseBuildingActor();
	virtual void PostInitializeComponents() override;
	virtual void BeginDestroy() override;
    
	virtual void On_Init();
	virtual void On_Delete();

    virtual void InitData(BaseBuildingData * _data);
    virtual void SaveData(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer);
    
	BuildingType        GetBuildingType();
    BlockTitleType      GetBlockTileType();
    
    ABlockActor *       GetOnBlockActor();
    void                SetOnBlockActor(ABlockActor * _blockActor);
    
	void                SetLevel(int _level);
	int	                GetLevel();

	void                SetDirection(BuildingDirection _dir);
	BuildingDirection   GetDirction();

	FRotator            DirectionRotation();

	void                SetIndex(BuildingIndex _index);
	BuildingIndex       GetIndex();
	
	virtual bool        IsInWorld();
 	virtual bool        IsInWorld(int _index);
    
public:
    UPROPERTY(VisibleDefaultsOnly, Category = BaseBuilding)
    UStaticMeshComponent * BaseMeshComponent;
    UPROPERTY(VisibleDefaultsOnly, Category = BaseBuilding)
    USkeletalMeshComponent * BaseSkeletalMeshComponent;

    
    
};
