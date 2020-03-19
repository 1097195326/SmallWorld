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
    

public:
	ABaseBuildingActor();

    virtual void InitData(BaseBuildingData * _data);
    virtual void SaveData(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer);
    
	FVector				GetInteractivePoint();

public:
    UPROPERTY(VisibleDefaultsOnly, Category = BaseBuilding)
    UStaticMeshComponent * BaseMeshComponent;
    UPROPERTY(VisibleDefaultsOnly, Category = BaseBuilding)
    USkeletalMeshComponent * BaseSkeletalMeshComponent;

	UPROPERTY(EditDefaultsOnly)
		FString		InteractivePointName;
    
};
