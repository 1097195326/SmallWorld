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
