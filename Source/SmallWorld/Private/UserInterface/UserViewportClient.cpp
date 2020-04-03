#include "UserViewportClient.h"
#include "UserController.h"
#include "Kismet/GameplayStatics.h"
#include "DataManager.h"
#include "PreviewActor.h"


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
	return PreviewActor != nullptr;
}
void UUserViewportClient::UpdatePriviewActor(FVector2D ScreenPosition, FString IconName /* = TEXT("") */)
{
	const AUserController * UserController = Cast<AUserController>(GetGameInstance()->GetFirstLocalPlayerController());
	
	FHitResult HitResult;
	
	TArray<TEnumAsByte<EObjectTypeQuery>> TrackObj;
	TrackObj.Add(UEngineTypes::ConvertToObjectType(ECC_GameTraceChannel3));

	UserController->GetHitResultAtScreenPosition(ScreenPosition, TrackObj, false, HitResult);

	if (HitResult.bBlockingHit && PreviewActor != HitResult.GetActor())
	{
		//UE_LOG(LogTemp, Log, TEXT("zhx : HitResult %s:%f,%f,%f"),*HitResult.GetActor()->GetName(), HitResult.ImpactPoint.X, HitResult.ImpactPoint.Y, HitResult.ImpactPoint.Z);
		if (!IconName.IsEmpty())
		{
			DestroyPriviewActor();

			FTransform SpawnPosition(HitResult.ImpactPoint);
			PreviewActor = GetWorld()->SpawnActorDeferred<APreviewActor>(APreviewActor::StaticClass(), SpawnPosition, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
			if (PreviewActor)
			{
				PreviewActor->SetMeshComponent(IconName);
				PreviewActor->FinishSpawning(SpawnPosition);
			}
		}
		if (PreviewActor)
		{
			PreviewActor->SetActorLocation(HitResult.ImpactPoint);
		}
	}

}
void UUserViewportClient::DropPriviewActor()
{
	if (PreviewActor)
	{
		//PreviewActor->GetActorRotation(), PreviewActor->GetActorLocation();
		//UWorld * world, const FVector & Location, const FRotator & Rotation, 
		FString IconName = PreviewActor->IconName;
		FVector Location = PreviewActor->GetActorLocation();
		FRotator Rotator = PreviewActor->GetActorRotation();
		DestroyPriviewActor();
		HordeData * UserHordeData = DataManager::GetInstance()->GetUserData()->GetHordeData();
		BaseBuildingData * BuildingData = UserHordeData->SpawnBuilding(IconName);
		if (!BuildingData->SpawnBuildingActor(GetWorld(), Location, Rotator))
		{
			UserHordeData->DestroyBuilding(BuildingData);
			UE_LOG(LogTemp,Log,TEXT("zhx:Warning:UUserViewportClient::DropPriviewActor:SpawnBuilding Fail"))
		}
		
		//DestroyPriviewActor();
	}
}

void UUserViewportClient::DestroyPriviewActor()
{
	if (PreviewActor)
	{
		PreviewActor->Destroy();
	}
	PreviewActor = nullptr;
}