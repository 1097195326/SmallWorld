#include "UserViewportClient.h"
#include "UserController.h"
#include "Kismet/GameplayStatics.h"
#include "DataManager.h"

#include "Classes/Animation/SkeletalMeshActor.h"
#include "Engine/StaticMeshActor.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"

UUserViewportClient * UUserViewportClient::UserViewportClientInstance = NULL;

void UUserViewportClient::PostInitProperties()
{
	Super::PostInitProperties();
	UserViewportClientInstance = this;
}
UUserViewportClient * UUserViewportClient::GetInstance()
{
	return UserViewportClientInstance;
}

void UUserViewportClient::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}
bool UUserViewportClient::HavePriviewActor()
{
	return PriviewActor.IsValid();
}
void UUserViewportClient::UpdatePriviewActor(FString IconName /* = TEXT("") */)
{
	const AUserController * UserController = Cast<AUserController>(GetGameInstance()->GetFirstLocalPlayerController());
	FHitResult HitResult;
#if PLATFORM_WINDOWS
	UserController->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
#elif PLATFORM_IOS || PLATFORM_ANDROID
	UserController->GetHitResultUnderFinger(ETouchIndex::Touch1, ECC_Visibility, false, HitResult);
#endif
	if (HitResult.bBlockingHit)
	{
		if (!IconName.IsEmpty())
		{
			DestroyPriviewActor();

			FTransform SpawnPosition(HitResult.ImpactPoint);

			FString MeshName = FString::Printf(TEXT("Mesh%s0"), *IconName);
			FAssetData MeshData = DataManager::GetInstance()->GetBuildingAssetDataByIconName(MeshName);

			AActor * Dactor = nullptr;

			if (MeshData.AssetClass == FName(TEXT("SkeletalMesh")))
			{
				USkeletalMesh * Mesh = Cast<USkeletalMesh>(MeshData.GetAsset());
				if (Mesh)
				{
					Dactor = UGameplayStatics::BeginDeferredActorSpawnFromClass(GetWorld(), ASkeletalMeshActor::StaticClass(), SpawnPosition, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
					ASkeletalMeshActor * SkeletalActor = Cast<ASkeletalMeshActor>(Dactor);
					if (SkeletalActor)
					{
						SkeletalActor->GetSkeletalMeshComponent()->SetSkeletalMesh(Mesh);
					}
				}
			}
			else if (MeshData.AssetClass == FName(TEXT("StaticMesh")))
			{
				UStaticMesh * Mesh = Cast<UStaticMesh>(MeshData.GetAsset());
				if (Mesh)
				{
					Dactor = UGameplayStatics::BeginDeferredActorSpawnFromClass(GetWorld(), AStaticMeshActor::StaticClass(), SpawnPosition, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
					AStaticMeshActor * StaticActor = Cast<AStaticMeshActor>(Dactor);
					if (StaticActor)
					{
						StaticActor->GetStaticMeshComponent()->SetStaticMesh(Mesh);
					}
				}
			}
			if (Dactor)
			{
				UGameplayStatics::FinishSpawningActor(Dactor, SpawnPosition);
				PriviewActor = MakeShareable(Dactor);
			}
		}
		if (PriviewActor.IsValid())
		{
			PriviewActor->SetActorLocation(HitResult.ImpactPoint);
		}
	}
}
void UUserViewportClient::DropPriviewActor()
{
	


}
void UUserViewportClient::DestroyPriviewActor()
{
	if (PriviewActor.IsValid())
	{
		PriviewActor->BeginDestroy();
	}
	PriviewActor.Reset();
}