#include "BaseBuildingActor.h"
#include "BlockActor.h"
#include "GameDataManager.h"


ABaseBuildingActor::ABaseBuildingActor()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	CollisionBoxComponent = CreateDefaultSubobject<UBoxComponent>("CollisionBoxComponent");
	CollisionBoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionBoxComponent->SetCollisionResponseToAllChannels(ECR_Block);
	CollisionBoxComponent->SetCollisionObjectType(GameActorTrace);

	CollisionBoxComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	BuildingData = nullptr;
    
	HotPointName = TEXT("HotPoint");
}
void ABaseBuildingActor::SetBuildingData(BaseBuildingDataClass * _data)
{
	GameData = BuildingData = _data;
    
}
void ABaseBuildingActor::SaveData(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	BuildingData->Serialization(Writer);
}
bool ABaseBuildingActor::SetMeshComponentByIconName(const FString & InIconName)
{
	bool IsOk = false;
	//FString MeshName = FString::Printf(TEXT("Mesh%s0"), *InIconName);
	FAssetData MeshData = GameDataManager::GetInstance()->GetBuildingAssetDataByIconName(InIconName);

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
				Component->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
				Component->SetCollisionResponseToAllChannels(ECR_Ignore);
				Component->SetCollisionObjectType(GameActorTrace);

				Component->RegisterComponent();
				IsOk = true;
			}
		}
	}
	return IsOk;
}
FVector ABaseBuildingActor::GetInteractivePoint()
{
	/*if (MeshComponent && MeshComponent->DoesSocketExist(FName(*HotPointName)))
	{
		return MeshComponent->GetSocketLocation(FName(*HotPointName));
	}*/
	return GetActorLocation();
}
