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
	return PriviewActor != nullptr;
}
void UUserViewportClient::UpdatePriviewActor(FVector2D ScreenPosition, FString IconName /* = TEXT("") */)
{
	const AUserController * UserController = Cast<AUserController>(GetGameInstance()->GetFirstLocalPlayerController());
	FHitResult HitResult;
	FVector2D MousePosition = ScreenPosition;
	//GetMousePosition(MousePosition);
#if PLATFORM_WINDOWS
	UserController->GetHitResultAtScreenPosition(ScreenPosition, ECC_Visibility, false, HitResult);
	//UserController->GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Visibility), false, HitResult);
	//UserController->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
#elif PLATFORM_IOS || PLATFORM_ANDROID
	UserController->GetHitResultUnderFinger(ETouchIndex::Touch1, ECC_Visibility, false, HitResult);
#endif
	if (HitResult.bBlockingHit)
	{
		UE_LOG(LogTemp, Log, TEXT("zhx : HitResult %s:%f,%f,%f"),*HitResult.GetActor()->GetName(), HitResult.ImpactPoint.X, HitResult.ImpactPoint.Y, HitResult.ImpactPoint.Z);
		if (!IconName.IsEmpty())
		{
			DestroyPriviewActor();

			FTransform SpawnPosition(HitResult.ImpactPoint);

			FString MeshName = FString::Printf(TEXT("Mesh%s0"), *IconName);
			FAssetData MeshData = DataManager::GetInstance()->GetBuildingAssetDataByIconName(MeshName);

			PriviewActor = nullptr;

			if (MeshData.AssetClass == FName(TEXT("SkeletalMesh")))
			{
				USkeletalMesh * Mesh = Cast<USkeletalMesh>(MeshData.GetAsset());
				if (Mesh)
				{
					PriviewActor = UGameplayStatics::BeginDeferredActorSpawnFromClass(GetWorld(), ASkeletalMeshActor::StaticClass(), SpawnPosition, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
					ASkeletalMeshActor * SkeletalActor = Cast<ASkeletalMeshActor>(PriviewActor);
					if (SkeletalActor)
					{
						//SkeletalActor->GetSkeletalMeshComponent()->Mobility = EComponentMobility::Movable;
						SkeletalActor->GetSkeletalMeshComponent()->SetSkeletalMesh(Mesh);
						SkeletalActor->GetSkeletalMeshComponent()->RegisterComponent();
					}
				}
			}
			else if (MeshData.AssetClass == FName(TEXT("StaticMesh")))
			{
				UStaticMesh * Mesh = Cast<UStaticMesh>(MeshData.GetAsset());
				if (Mesh)
				{
					PriviewActor = UGameplayStatics::BeginDeferredActorSpawnFromClass(GetWorld(), AStaticMeshActor::StaticClass(), SpawnPosition, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
					AStaticMeshActor * StaticActor = Cast<AStaticMeshActor>(PriviewActor);
					if (StaticActor)
					{
						StaticActor->GetStaticMeshComponent()->Mobility = EComponentMobility::Movable;
						StaticActor->GetStaticMeshComponent()->SetStaticMesh(Mesh);
						StaticActor->GetStaticMeshComponent()->RegisterComponent();
					}
				}
			}
			if (PriviewActor)
			{
				UGameplayStatics::FinishSpawningActor(PriviewActor, SpawnPosition);
			}
		}
		if (PriviewActor)
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
	/*if (PriviewActor)
	{
		PriviewActor->BeginDestroy();
	}
	PriviewActor = nullptr;*/
}