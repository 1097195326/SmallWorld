#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ConstructorHelpers.h"
#include "Engine/StaticMesh.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/MeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include <vector>

#include "BaseBuildingActor.generated.h"

using namespace std;

UCLASS()
class ABaseBuildingActor : public AActor
{
	GENERATED_BODY()

public:
	ABaseBuildingActor();

	UPROPERTY(VisibleDefaultsOnly, Category = BaseBuilding)
		UStaticMeshComponent * BaseMeshComponent;
	UPROPERTY(VisibleDefaultsOnly, Category = BaseBuilding)
		USkeletalMeshComponent * BaseSkeletalMeshComponent;

	virtual FBox GetBuildingBound();
	virtual float GetBuidlingWidth();
	virtual float GetBuildingHeight();
	virtual float GetBuildingLength();

	virtual FVector GetXYLeftBottomPoint();
	virtual FVector GetXYLeftTopPoint();
	virtual FVector GetXYRightBottomPoint();
	virtual FVector GetXYRightTopPoint();

};