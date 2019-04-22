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
enum BuildingDirection
{
	Dir_None,
	Dir_Corner_LeftBottom,
	Dir_Corner_LeftTop,
	Dir_Corner_RightBottom,
	Dir_Corner_RightTop,

	Dir_Left,
	Dir_Right,
	Dir_Top,
	Dir_Bottom,
	Dir_Center,

};
static int  BoundSize = 0;
static int  WorldSize = 1;
static int	CitySize = 15;
static int  CastleControllSize = 11;
static int  CastleSize = 7;
static int	CastleCenterSize = 3;
static float TitleSize = 2500.f;




UCLASS()
class ABaseBuildingActor : public AActor
{
	GENERATED_BODY()
protected:
	FBuildingIndex mIndex;
	BuildingDirection mDirection;

public:
	ABaseBuildingActor();
	virtual void PostInitializeComponents() override;
	virtual void BeginDestroy() override;

	virtual void On_Init();
	virtual void On_Delete();

	UPROPERTY(VisibleDefaultsOnly, Category = BaseBuilding)
		UStaticMeshComponent * BaseMeshComponent;
	UPROPERTY(VisibleDefaultsOnly, Category = BaseBuilding)
		USkeletalMeshComponent * BaseSkeletalMeshComponent;

	void SetDirection(BuildingDirection _dir);
	BuildingDirection GetDirction();

	FRotator DirectionRotation();

	void SetIndex(FBuildingIndex _index);
	FBuildingIndex GetIndex();
	
	virtual bool IsInWorld();
 	virtual bool IsInWorld(int _index);

	virtual FBox GetBuildingBound();
	virtual float GetBuidlingWidth();
	virtual float GetBuildingHeight();
	virtual float GetBuildingLength();

	virtual FVector GetCenterPoint();
	virtual FVector GetXYLeftBottomPoint();
	virtual FVector GetXYLeftTopPoint();
	virtual FVector GetXYRightBottomPoint();
	virtual FVector GetXYRightTopPoint();

	virtual FBuildingIndex GetCenterIndex();
	virtual FBuildingIndex GetXYLeftBottomIndex();
	virtual FBuildingIndex GetXYLeftTopIndex();
	virtual FBuildingIndex GetXYRightBottomIndex();
	virtual FBuildingIndex GetXYRightTopIndex();
};