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

//USTRUCT()
struct FBuildingIndex
{
	//GENERATED_BODY()
	int X;
	int Y;
	FBuildingIndex() {}
	FBuildingIndex(int _x, int _y) :X(_x), Y(_y)
	{

	}
};
static float TitleSize = 2500.f;
static int	CitySize = 11;
static int  WorldSize = 2;


UCLASS()
class ABaseBuildingActor : public AActor
{
	GENERATED_BODY()
protected:
	FBuildingIndex Index;

public:
	ABaseBuildingActor();

	UPROPERTY(VisibleDefaultsOnly, Category = BaseBuilding)
		UStaticMeshComponent * BaseMeshComponent;
	UPROPERTY(VisibleDefaultsOnly, Category = BaseBuilding)
		USkeletalMeshComponent * BaseSkeletalMeshComponent;

	void SetIndex(FBuildingIndex _index);
	FBuildingIndex GetIndex();

	virtual FBox GetBuildingBound();
	virtual float GetBuidlingWidth();
	virtual float GetBuildingHeight();
	virtual float GetBuildingLength();

	virtual FVector GetXYLeftBottomPoint();
	virtual FVector GetXYLeftTopPoint();
	virtual FVector GetXYRightBottomPoint();
	virtual FVector GetXYRightTopPoint();

};