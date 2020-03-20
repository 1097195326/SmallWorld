#include "BaseBuildingActor.h"
#include "BlockActor.h"
#include "DataManager.h"

ABaseBuildingActor::ABaseBuildingActor()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	BuildingData = nullptr;
    
	HotPointName = TEXT("HotPoint");
}
void ABaseBuildingActor::SetBuildingData(BaseBuildingData * _data)
{
	BuildingData = _data;
    
}
void ABaseBuildingActor::SaveData(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	BuildingData->Serialization(Writer);
}
bool ABaseBuildingActor::SetMeshComponent(const FString & InIconName)
{
	bool IsOk = false;
	FString MeshName = FString::Printf(TEXT("Mesh%s0"), *InIconName);
	FAssetData MeshData = DataManager::GetInstance()->GetBuildingAssetDataByIconName(MeshName);

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
