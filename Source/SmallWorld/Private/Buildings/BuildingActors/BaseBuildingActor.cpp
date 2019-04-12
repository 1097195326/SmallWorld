#include "BaseBuildingActor.h"


ABaseBuildingActor::ABaseBuildingActor()
{
	BaseMeshComponent = nullptr;
	BaseSkeletalMeshComponent = nullptr;
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