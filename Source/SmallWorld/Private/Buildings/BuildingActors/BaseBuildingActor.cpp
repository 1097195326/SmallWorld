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

void ABaseBuildingActor::InitData(BaseBuildingData * _data)
{
    mData = _data;
    
}
void ABaseBuildingActor::SaveData(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
    mData->Serialization(Writer);
}

BuildingType ABaseBuildingActor::GetBuildingType()
{
    return mData->mType;
}
void ABaseBuildingActor::SetLevel(int _level)
{
	mData->mLevel = _level;
}
int ABaseBuildingActor::GetLevel()
{
	return mData->mLevel;
}
FString ABaseBuildingActor::GetMeshPath()
{
	FString Path;
	switch (mData->mLevel)
	{
	case 0:
		Path = MeshPathLevel_0;
		break;
	case 1:
		Path = MeshPathLevel_1;
		break;
	case 2:
		Path = MeshPathLevel_2;
		break;
	case 3:
		Path = MeshPathLevel_3;
		break;
	case 4:
		Path = MeshPathLevel_4;
		break;
	case 5:
		Path = MeshPathLevel_5;
		break;
	default:
		break;
	}
	return Path;
}

void ABaseBuildingActor::SetDirection(BuildingDirection _dir)
{
	mData->mDirection = _dir;
}
BuildingDirection ABaseBuildingActor::GetDirction()
{
	return mData->mDirection;
}
FRotator ABaseBuildingActor::DirectionRotation()
{
	FRotator Rotator(ForceInit);
	switch (mData->mDirection)
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
void ABaseBuildingActor::SetIndex(BuildingIndex _index)
{
	mData->mIndex = _index;
}
BuildingIndex ABaseBuildingActor::GetIndex()
{
	return mData->mIndex;
}
bool ABaseBuildingActor::IsInWorld()
{
	return IsInWorld(mData->mIndex.X) && IsInWorld(mData->mIndex.Y);
}
bool ABaseBuildingActor::IsInWorld(int _index)
{
	return _index >= BoundSize && _index <= WorldSize;
}
