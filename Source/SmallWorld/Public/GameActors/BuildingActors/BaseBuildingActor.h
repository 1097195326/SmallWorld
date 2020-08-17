#pragma once

#include "CoreMinimal.h"
#include "GameActor.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/MeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SmallWorldInstance.h"
#include <vector>
#include <list>
#include "BaseBuildingActor.generated.h"

using namespace std;
class BaseBuildingDataClass;

UCLASS()
class ABaseBuildingActor : public AGameActor
{
public:
	GENERATED_BODY()
	ABaseBuildingActor();

    void SetBuildingData(BaseBuildingDataClass * InData);
    virtual void SaveData(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer);
	virtual bool SetMeshComponentByIconName(const FString & InIconName);
	

	FVector				GetInteractivePoint();
protected:
	BaseBuildingDataClass * BuildingData;

public:
	/*UPROPERTY(VisibleDefaultsOnly, Category = BaseBuilding)
	UMeshComponent * MeshComponent;*/

	UPROPERTY(EditDefaultsOnly)
		FString		HotPointName;
    
};
