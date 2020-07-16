#include "PreviewActor.h"
#include "Engine/StaticMesh.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameDataManager.h"

APreviewActor::APreviewActor()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

}
bool APreviewActor::SetMeshComponent(const FString & InIconName)
{
	bool IsOk = false;
	IconName = InIconName;

	FString MeshName = FString::Printf(TEXT("Mesh%s0"), *InIconName);
	FAssetData MeshData = GameDataManager::GetInstance()->GetBuildingAssetDataByIconName(MeshName);

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