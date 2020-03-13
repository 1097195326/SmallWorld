#include "UserController.h"
#include "Kismet/GameplayStatics.h"
#include "GameActor.h"


#include "DataManager.h"
#include "Classes/Animation/SkeletalMeshActor.h"
#include "Engine/StaticMeshActor.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"

void AUserController::On_Init()
{
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
bool AUserController::InputKey(FKey Key, EInputEvent EventType, float AmountDepressed, bool bGamepad)
{
	if (Key == EKeys::LeftMouseButton && EventType == IE_Pressed)
	{
		FHitResult HitResult;
		GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Visibility), false, HitResult);
		ALandscape * Landscape = Cast<ALandscape>(HitResult.GetActor());
		AGameActor * GameActor = Cast<AGameActor>(HitResult.GetActor());

		//FString MeshName = FString::Printf(TEXT("Mesh%s0"), TEXT("CommandCenter"));
		//FAssetData MeshData = DataManager::GetInstance()->GetBuildingAssetDataByIconName(MeshName);

		//AActor * PriviewActor = nullptr;
		//const FTransform SpawnPosition(HitResult.ImpactPoint);

		//UStaticMesh * Mesh = Cast<UStaticMesh>(MeshData.GetAsset());
		//if (Mesh)
		//{
		//	FActorSpawnParameters Par;
		//	Par.Owner = this;
		//	Par.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		//	
		//	AStaticMeshActor * StaticActor = GetWorld()->SpawnActor<AStaticMeshActor>(AStaticMeshActor::StaticClass(), Par);
		//	//AStaticMeshActor * StaticActor = Cast<AStaticMeshActor>(PriviewActor);
		//	if (StaticActor)
		//	{
		//		StaticActor->GetStaticMeshComponent()->Mobility = EComponentMobility::Movable;
		//		bool success = StaticActor->GetStaticMeshComponent()->SetStaticMesh(Mesh);
		//		StaticActor->GetStaticMeshComponent()->RegisterComponent();
		//		StaticActor->RegisterAllComponents();
		//		StaticActor->SetActorLocation(HitResult.ImpactPoint);
		//	}
		//}
		

		if (Landscape)
		{

		}else if (GameActor && CurrentControllType == ECT_ShowSomething)
		{

		}
	}else if (Key == EKeys::LeftMouseButton && EventType == IE_Repeat)
	{

	}else if (Key == EKeys::LeftMouseButton && EventType == IE_Released)
	{
		FHitResult HitResult;
		GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Visibility), false, HitResult);
		ALandscape * Landscape = Cast<ALandscape>(HitResult.GetActor());
		if (Landscape)
		{

		}
	}
	return Super::InputKey(Key, EventType, AmountDepressed, bGamepad);
}
bool AUserController::InputTouch(uint32 Handle, ETouchType::Type Type, const FVector2D& TouchLocation, float Force, FDateTime DeviceTimestamp, uint32 TouchpadIndex)
{

	return Super::InputTouch(Handle, Type, TouchLocation, Force, DeviceTimestamp, TouchpadIndex);
}
bool AUserController::InputAxis(FKey Key, float Delta, float DeltaTime, int32 NumSamples, bool bGamepad)
{

	return Super::InputAxis(Key, Delta, DeltaTime, NumSamples, bGamepad);
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