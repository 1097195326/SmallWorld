#include "BaseBuildingActor.h"


ABaseBuildingActor::ABaseBuildingActor()
{
	BaseMeshComponent = nullptr;
	BaseSkeletalMeshComponent = nullptr;
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