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
#include "UserGameInstance.h"
#include <vector>
#include <list>
#include "CastleTileActor.h"
#include "GameConfig.h"
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
	BaseBuildingDataClass * GetBuildingData() { return BuildingData; }
	
	virtual void SaveData(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer);
	virtual bool SetMeshComponentByIconName(const FString & InIconName);
	
	void	SetCastleTileActor(ACastleTileActor * InActor) { CastleTileActor = InActor; }
	ACastleTileActor * GetCastleTileActor() { return CastleTileActor; }

	FVector				GetInteractivePoint();

protected:
	BaseBuildingDataClass * BuildingData;
	ACastleTileActor *		CastleTileActor;
	int32 CurrentUpdateInterval;
public:
	/*UPROPERTY(VisibleDefaultsOnly, Category = BaseBuilding)
	UMeshComponent * MeshComponent;*/

	UPROPERTY(EditDefaultsOnly)
		FString		HotPointName;
	UPROPERTY(VisibleDefaultsOnly)
		UBoxComponent   * CollisionBoxComponent;
};
