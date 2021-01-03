#include "UserController.h"
#include "Kismet/GameplayStatics.h"
#include "GameDataManager.h"
#include "GameManager.h"
#include "PreviewActor.h"
#include "GameConfig.h"
#include "UIControllerManager.h"
#include "CastleTileActor.h"
#include "GroundTileActor.h"
#include "SoldierPawn.h"

AUserController * AUserController::Instance = nullptr;

AUserController * AUserController::GetInstance()
{
	return Instance;
}
void AUserController::On_Init()
{
	Instance = this;

	CurrentLandscapeInfo = nullptr;
	CurrentLandscape = nullptr;
	CurrentControllType = ECT_None;

	FInputModeGameAndUI InputMode;
	InputMode.SetHideCursorDuringCapture(false);
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	SetInputMode(InputMode);
	
	bShowMouseCursor = true;


}
void AUserController::On_Start()
{
	CurrentLandscapeInfo = nullptr;

	TArray<AActor*> AllLandscape;
	/*UGameplayStatics::GetAllActorsOfClass(this, ALandscape::StaticClass(), AllLandscape);
	for (int i = 0; i < AllLandscape.Num(); i++)
	{
		ALandscape * Landscape = Cast<ALandscape>(AllLandscape[i]);
		if (Landscape)
		{
			CurrentLandscape = Landscape;
			CurrentLandscapeInfo = Landscape->CreateLandscapeInfo();
			break;
		}
	}*/

}
void AUserController::On_Tick(float delta)
{

}
void AUserController::On_Delete()
{

}

AActor * AUserController::TrySelectGameActor(FVector2D ScreenPosition)
{

	TArray<TEnumAsByte<EObjectTypeQuery>> TrackObj;
	TrackObj.Add(UEngineTypes::ConvertToObjectType(GameActorTrace));
	TrackObj.Add(UEngineTypes::ConvertToObjectType(SoldierTrace));

	FHitResult HitResult;
	GetHitResultAtScreenPosition(ScreenPosition, TrackObj,false,HitResult);
	if (HitResult.bBlockingHit)
	{
		AGameActor* GameActor = Cast<AGameActor>(HitResult.GetActor());
		AGroundTileActor* TileActor = Cast<AGroundTileActor>(HitResult.GetActor());
		ASoldierPawn * SoldierPawn = Cast<ASoldierPawn>(HitResult.GetActor());
		if (SoldierPawn)
		{
			CurrentSelectedSoldier = SoldierPawn;
			GetCurrentUIController->SelectGameActor(SoldierPawn);
			int32 MoveDis = SoldierPawn->GetSoldierData()->GetMoveRange();
			AGroundTileActor* MainTile = SoldierPawn->GetOriginGroundTile();
			if (MainTile)
			{
				TArray<AGroundTileActor*>  AroundTiles;
				GameManager::GetGroundTileAroundSoldier(MainTile, MoveDis, AroundTiles);

				MainTile->ShowFlags(true, false);
				for (auto IterActor : AroundTiles)
				{
					IterActor->ShowFlags(false, true);
				}

			}
			return SoldierPawn;
		}
		else if (TileActor)
		{
			if (CurrentSelectedSoldier)
			{
				int32 MoveDis = CurrentSelectedSoldier->GetSoldierData()->GetMoveRange();
				AGroundTileActor* MainTile = CurrentSelectedSoldier->GetOriginGroundTile();
				TArray<AGroundTileActor*>  AroundTiles;
				GameManager::GetGroundTileAroundSoldier(MainTile, MoveDis, AroundTiles);
				if (AroundTiles.Contains(TileActor))
				{
					CurrentSelectedSoldier->SetTargetGroundTile(TileActor);
					CurrentSelectedSoldier->GetOriginGroundTile()->SetBusy(true);
					CurrentSelectedSoldier->GetTargetGroundTile()->SetBusy(true);
					//CurrentSelectedSoldier->SetMoveLocation(TileActor->GetActorLocation());
				}
				else
				{
					// show why

				}
				CurrentSelectedSoldier = nullptr;
			}
			else
			{
				GetCurrentUIController->SelectGameActor(TileActor);
			}
			return TileActor;
		}else if(GameActor)
		{
			CurrentSelectedSoldier = nullptr;
			GetCurrentUIController->SelectGameActor(GameActor);
			return GameActor;
		}
	}
	else
	{
		CurrentSelectedSoldier = nullptr;
	}
	return nullptr;
}
bool AUserController::HavePriviewActor()
{
	return PreviewActor != nullptr;
}
void AUserController::UpdatePriviewActor(FVector2D ScreenPosition, FString IconName /* = TEXT("") */)
{
	FHitResult HitResult;

	TArray<TEnumAsByte<EObjectTypeQuery>> TrackObj;
	TrackObj.Add(UEngineTypes::ConvertToObjectType(LandscapeTrace));

	GetHitResultAtScreenPosition(ScreenPosition, TrackObj, false, HitResult);

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
void AUserController::DropPriviewActor()
{
	if (PreviewActor)
	{
		//PreviewActor->GetActorRotation(), PreviewActor->GetActorLocation();
		//UWorld * world, const FVector & Location, const FRotator & Rotation, 
		FString IconName = PreviewActor->IconName;
		FVector Location = PreviewActor->GetActorLocation();
		FRotator Rotator = PreviewActor->GetActorRotation();
		DestroyPriviewActor();
		HordeDataClass * UserHordeData = GameDataManager::GetInstance()->GetUserData()->GetHordeData();
		BaseBuildingDataClass * BuildingData = UserHordeData->SpawnBuildingData(IconName);
		if (BuildingData->SpawnBuildingActor(GetWorld(), FTransform(Rotator,Location),0) == nullptr)
		{
			UserHordeData->DestroyBuilding(BuildingData);
			UE_LOG(LogTemp, Log, TEXT("zhx:Warning:UUserViewportClient::DropPriviewActor:SpawnBuilding Fail"))
		}

		//DestroyPriviewActor();
	}
}

void AUserController::DestroyPriviewActor()
{
	if (PreviewActor)
	{
		PreviewActor->Destroy();
	}
	PreviewActor = nullptr;
}
void AUserController::ChangeControllType(EControllType ControllType)
{
	CurrentControllType = ControllType;
}
void AUserController::LandscapePaint(ALandscape * Landscape, ULandscapeInfo * LandscapeInfo, FVector Location, float Radius, float Falloff)
{
	if (Landscape && LandscapeInfo)
	{
		ULandscapeLayerInfoObject * LayerInfo = LandscapeInfo->GetLayerInfoByName("auto");

		FCLandscapeToolTarget  ToolTarget;
		ToolTarget.LandscapeInfo = LandscapeInfo;
		ToolTarget.LayerInfo = LayerInfo;
		ToolTarget.TargetType = ECLandscapeToolTargetType::Weightmap;

		FVector LandscapePos = Landscape->LandscapeActorToWorld().InverseTransformPosition(Location);

		TArray<FCLandscapeToolInteractorPosition> InteractorPositions;
		InteractorPositions.Empty(1);
		InteractorPositions.Emplace(FVector2D(LandscapePos), false);

		FCLandscapeBrushCircle_Smooth * Brush = new FCLandscapeBrushCircle_Smooth(LandscapeInfo, 500.f, 0.5f);
		FCLandscapeToolStrokePaint * StrokePaint = new FCLandscapeToolStrokePaint(ToolTarget);

		StrokePaint->Apply(Brush, InteractorPositions);
	}
}