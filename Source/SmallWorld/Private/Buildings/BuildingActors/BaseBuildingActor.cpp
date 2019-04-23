#include "BaseBuildingActor.h"


ABaseBuildingActor::ABaseBuildingActor()
{
	BaseMeshComponent = nullptr;
	BaseSkeletalMeshComponent = nullptr;
	mDirection = Dir_None;

}
void ABaseBuildingActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	On_Init();
}
void ABaseBuildingActor::BeginDestroy()
{
	Super::BeginDestroy();
	On_Delete();
}
void ABaseBuildingActor::On_Init()
{

}
void ABaseBuildingActor::On_Delete()
{

}
FBox ABaseBuildingActor::GetBuildingBound()
{
	return GetComponentsBoundingBox(true);
}
float ABaseBuildingActor::GetBuidlingWidth()
{
	return GetBuildingBound().GetSize().X;
}
float ABaseBuildingActor::GetBuildingLength()
{
	return GetBuildingBound().GetSize().Y;
}
float ABaseBuildingActor::GetBuildingHeight()
{
	return GetBuildingBound().GetSize().Z;
}
FVector ABaseBuildingActor::GetCenterPoint()
{
	FVector Center, Extent;
	GetBuildingBound().GetCenterAndExtents(Center,Extent);
	return Center;
}
FVector ABaseBuildingActor::GetXYLeftBottomPoint()
{
	return GetBuildingBound().Min;
}
FVector ABaseBuildingActor::GetXYLeftTopPoint()
{
	return GetBuildingBound().Min + FVector(GetBuildingLength(),0,0);
}
FVector ABaseBuildingActor::GetXYRightBottomPoint()
{
	return GetBuildingBound().Min + FVector(0,GetBuidlingWidth(),0);
}
FVector ABaseBuildingActor::GetXYRightTopPoint()
{
	return GetBuildingBound().Min + FVector(GetBuildingLength(),GetBuidlingWidth(),0);
}
void ABaseBuildingActor::SetDirection(BuildingDirection _dir)
{
	mDirection = _dir;
}
BuildingDirection ABaseBuildingActor::GetDirction()
{
	return mDirection;
}
FRotator ABaseBuildingActor::DirectionRotation()
{
	FRotator Rotator(ForceInit);
	switch (mDirection)
	{
	case Dir_None:
		break;
	case Dir_Corner_City_LeftBottom:
	case Dir_Corner_Castle_LeftBottom:
		Rotator.Yaw = -90.f;
		break;
	case Dir_Corner_City_LeftTop:
	case Dir_Corner_Castle_LeftTop:
		break;
	case Dir_Corner_City_RightBottom:
	case Dir_Corner_Castle_RightBottom:
		Rotator.Yaw = 180.f;
		break;
	case Dir_Corner_City_RightTop:
	case Dir_Corner_Castle_RightTop:
		Rotator.Yaw = 90.f;
		break;
	case Dir_CityEdge_Left:
	case Dir_CastleEdge_Left:
		
		break;
	case Dir_CityEdge_Right:
	case Dir_CastleEdge_Right:
		Rotator.Yaw = 180.f;
		break;
	case Dir_CityEdge_Top:
	case Dir_CastleEdge_Top:
		Rotator.Yaw = 90.f;
		break;
	case Dir_CityEdge_Bottom:
	case Dir_CastleEdge_Bottom:
		Rotator.Yaw = -90.f;
		break;
	case Dir_City_Center:
		break;
	default:
		break;
	}

	return Rotator;
}
void ABaseBuildingActor::SetIndex(FBuildingIndex _index)
{
	mIndex = _index;
}
FBuildingIndex ABaseBuildingActor::GetIndex()
{
	return mIndex;
}
bool ABaseBuildingActor::IsInWorld()
{
	return IsInWorld(mIndex.X) && IsInWorld(mIndex.Y);
}
bool ABaseBuildingActor::IsInWorld(int _index)
{
	return _index >= BoundSize && _index <= WorldSize;
}
FBuildingIndex ABaseBuildingActor::GetCenterIndex()
{
	return FBuildingIndex();
}
FBuildingIndex ABaseBuildingActor::GetXYLeftBottomIndex()
{
	return FBuildingIndex();
}
FBuildingIndex ABaseBuildingActor::GetXYLeftTopIndex()
{
	return FBuildingIndex();
}
FBuildingIndex ABaseBuildingActor::GetXYRightBottomIndex()
{
	return FBuildingIndex();
}
FBuildingIndex ABaseBuildingActor::GetXYRightTopIndex()
{
	return FBuildingIndex();
}