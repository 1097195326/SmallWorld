#include "BaseBuildingActor.h"
#include "BlockActor.h"

ABaseBuildingActor::ABaseBuildingActor()
{
	BaseMeshComponent = nullptr;
	BaseSkeletalMeshComponent = nullptr;
	
	mData = nullptr;
    
	InteractivePointName = TEXT("InteractivePoint");
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
FVector ABaseBuildingActor::GetInteractivePoint()
{
	if (BaseSkeletalMeshComponent && BaseSkeletalMeshComponent->DoesSocketExist(FName(*InteractivePointName)))
	{
		return BaseSkeletalMeshComponent->GetSocketLocation(FName(*InteractivePointName));
	}else if (BaseMeshComponent && BaseMeshComponent->DoesSocketExist(FName(*InteractivePointName)))
	{
		return BaseMeshComponent->GetSocketLocation(FName(*InteractivePointName));
	}
	return GetActorLocation();
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
void ABaseBuildingActor::SetOnBlockActor(ABlockActor * _blockActor)
{
    mOnBlockActor = _blockActor;
}
ABlockActor * ABaseBuildingActor::GetOnBlockActor()
{
    return mOnBlockActor;
}