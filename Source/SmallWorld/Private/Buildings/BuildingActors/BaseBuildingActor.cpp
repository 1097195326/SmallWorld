#include "BaseBuildingActor.h"
#include "BlockActor.h"

ABaseBuildingActor::ABaseBuildingActor()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	mData = nullptr;
    
	HotPointName = TEXT("HotPoint");
}
void ABaseBuildingActor::InitData(BaseBuildingData * _data)
{
    mData = _data;
    
}
void ABaseBuildingActor::SaveData(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
    mData->Serialization(Writer);
}
bool ABaseBuildingActor::SetMeshComponent(const FAssetData & MeshData)
{
	bool IsOk = false;
	if (MeshData.AssetClass == FName(TEXT("SkeletalMesh")))
	{
		USkeletalMesh * Mesh = Cast<USkeletalMesh>(MeshData.GetAsset());
		if (Mesh)
		{
			USkeletalMeshComponent* Component = NewObject<USkeletalMeshComponent>(this);
			//Component->Mobility = EComponentMobility::Movable;
			if (Component->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform))
			{
				Component->SetSkeletalMesh(Mesh);
				Component->RegisterComponent();
				MeshComponent = Component;
				IsOk = true;
			}
		}
	}
	else if (MeshData.AssetClass == FName(TEXT("StaticMesh")))
	{
		UStaticMesh * Mesh = Cast<UStaticMesh>(MeshData.GetAsset());
		if (Mesh)
		{
			UStaticMeshComponent* Component = NewObject<UStaticMeshComponent>(this);
			if (Component->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform))
			{
				Component->Mobility = EComponentMobility::Movable;
				Component->SetStaticMesh(Mesh);
				Component->RegisterComponent();
				MeshComponent = Component;
				IsOk = true;
			}
		}
	}
	return IsOk;
}
FVector ABaseBuildingActor::GetInteractivePoint()
{
	if (MeshComponent && MeshComponent->DoesSocketExist(FName(*HotPointName)))
	{
		return MeshComponent->GetSocketLocation(FName(*HotPointName));
	}
	return GetActorLocation();
}
