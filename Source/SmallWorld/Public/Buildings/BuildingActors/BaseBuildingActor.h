#pragma once

#include "CoreMinimal.h"
#include "GameActor.h"
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




class ABlockActor;

UCLASS()
class ABaseBuildingActor : public AGameActor
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

    virtual void InitData(BaseBuildingData * _data);
    virtual void SaveData(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer);
    
	FVector				GetInteractivePoint();

	BuildingType        GetBuildingType();
    
    ABlockActor *       GetOnBlockActor();
    void                SetOnBlockActor(ABlockActor * _blockActor);
    
	void                SetLevel(int _level);
	int	                GetLevel();

	FRotator            DirectionRotation() {};

	
	virtual bool        IsInWorld() {
		return true;
	}
	virtual bool        IsInWorld(int _index) { return true; }
    
public:
    UPROPERTY(VisibleDefaultsOnly, Category = BaseBuilding)
    UStaticMeshComponent * BaseMeshComponent;
    UPROPERTY(VisibleDefaultsOnly, Category = BaseBuilding)
    USkeletalMeshComponent * BaseSkeletalMeshComponent;

	UPROPERTY(EditDefaultsOnly)
		FString		InteractivePointName;
    
};
