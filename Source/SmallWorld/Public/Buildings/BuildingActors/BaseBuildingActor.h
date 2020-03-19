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
public:
	GENERATED_BODY()
	ABaseBuildingActor();

    virtual void InitData(BaseBuildingData * InData);
    virtual void SaveData(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer);
	virtual bool SetMeshComponent(const FAssetData & MeshData);

	FVector				GetInteractivePoint();
protected:
	BaseBuildingData * mData;

public:
	UPROPERTY(VisibleDefaultsOnly, Category = BaseBuilding)
	UMeshComponent * MeshComponent;

	UPROPERTY(EditDefaultsOnly)
		FString		HotPointName;
    
};
