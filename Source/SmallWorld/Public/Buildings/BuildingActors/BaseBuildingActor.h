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
#include "BaseBuildingData.h"
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

enum CityOrientation
{
	O_None,
	// OutControll 
	CornerOutControll_LeftBottom,
	CornerOutControll_LeftTop,
	CornerOutControll_RightBottom,
	CornerOutControll_RightTop,

	CenterOutControll_Left,
	CenterOutControll_Right,
	CenterOutControll_Top,
	CenterOutControll_Bottom,

	OutSkirtOutControll_LeftBottom,
	OutSkirtOutControll_LeftTop,
	OutSkirtOutControll_RightBottom,
	OutSkirtOutControll_RightTop,
	OutSkirtOutControll_TopLeft,
	OutSkirtOutControll_TopRight,
	OutSkirtOutControll_BottomLeft,
	OutSkirtOutControll_BottomRight,

	FarmOutControll_LeftBottom,
	FarmOutControll_LeftTop,
	FarmOutControll_RightBottom,
	FarmOutControll_RightTop,
	FarmOutControll_TopLeft,
	FarmOutControll_TopRight,
	FarmOutControll_BottomLeft,
	FarmOutControll_BottomRight,
	// Controll
	CornerControll_LeftBottom,
	CornerControll_LeftTop,
	CornerControll_RightBottom,
	CornerControll_RightTop,

	CenterControll_Left,
	CenterControll_Right,
	CenterControll_Top,
	CenterControll_Bottom,

	FarmControll_LeftBottom,
	FarmControll_LeftTop,
	FarmControll_RightBottom,
	FarmControll_RightTop,
	FarmControll_TopLeft,
	FarmControll_TopRight,
	FarmControll_BottomLeft,
	FarmControll_BottomRight,
	// In Castle
	CornerCastle_LeftBottom,
	CornerCastle_LeftTop,
	CornerCastle_RightBottom,
	CornerCastle_RightTop,

	CenterCastle_Left,
	CenterCastle_Right,
	CenterCastle_Top,
	CenterCastle_Bottom,
	// City Center
	Center_City,
	CenterOfCenter_City,


};
enum BuildingDirection
{
	Dir_None,
	
    Dir_Corner_City_LeftBottom,
	Dir_Corner_City_LeftTop,
	Dir_Corner_City_RightBottom,
	Dir_Corner_City_RightTop,

	Dir_CityEdge_Left,
	Dir_CityEdge_Right,
	Dir_CityEdge_Top,
	Dir_CityEdge_Bottom,
    
    Dir_Corner_Castle_LeftBottom,
    Dir_Corner_Castle_LeftTop,
    Dir_Corner_Castle_RightBottom,
    Dir_Corner_Castle_RightTop,
    
    Dir_CastleEdge_Left,
    Dir_CastleEdge_Right,
    Dir_CastleEdge_Top,
    Dir_CastleEdge_Bottom,
    
    
	Dir_City_Center,

};

const int  BoundSize = 0;
const int  WorldSize = 1;
const int	CitySize = 15;
const int  CastleControllSize = 11;
const int  CastleSize = 7;
const int	CastleCenterSize = 3;
const float TitleSize = 2500.f;
const float WallSize = 625.f;



UCLASS()
class ABaseBuildingActor : public AActor
{
	GENERATED_BODY()
protected:
	BuildingType   mType;
	FBuildingIndex mIndex;
	BuildingDirection mDirection;
	
	int					mLevel;
	int					mMaxLevel;

	FString  MeshPathLevel_0;
	FString  MeshPathLevel_1;
	FString  MeshPathLevel_2;
	FString  MeshPathLevel_3;
	FString  MeshPathLevel_4;
	FString  MeshPathLevel_5;


	virtual FString GetMeshPath();

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

	BuildingType GetBuildingType();

	void SetLevel(int _level);
	int	GetLevel();

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
