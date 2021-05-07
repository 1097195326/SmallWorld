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


	CurrentUpdateInterval = 0;
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
bool ABaseBuildingActor::SetMeshComponentByIconName(const FString & InName)
{
	bool IsOk = false;
	//StaticMesh_CommandCenter_0
	//FString MeshName = FString::Printf(TEXT("Mesh%s0"), *InIconName);
	//FAssetData MeshData = GameDataManager::GetInstance()->GetBuildingAssetDataByIconName(InName);
	const FResourceTableRow * ResourceRow = GameDataManager::GetInstance()->GetGameConfigData()->GetResourceTableRowByName(InName);
	UObject * ResourceObject = ResourceRow->ResourcePath.LoadSynchronous();
	if (ResourceObject)
	{
		if (ResourceObject->IsA<USkeletalMesh>())
		{
			USkeletalMesh * Mesh = Cast<USkeletalMesh>(ResourceObject);
			if (Mesh)
			{
				USkeletalMeshComponent* Component = NewObject<USkeletalMeshComponent>(this);
				//Component->Mobility = EComponentMobility::Movable;
				if (Component->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform))
				{
					Component->SetSkeletalMesh(Mesh);
					Component->SetRelativeRotation(ResourceRow->RelativeRotation);
					Component->SetRelativeScale3D(ResourceRow->RelativeScale);
					Component->RegisterComponent();
					IsOk = true;
				}
			}
		}
		else if (ResourceObject->IsA<UStaticMesh>())
		{
			UStaticMesh * Mesh = Cast<UStaticMesh>(ResourceObject);
			if (Mesh)
			{
				UStaticMeshComponent* Component = NewObject<UStaticMeshComponent>(this);
				if (Component->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform))
				{
					Component->Mobility = EComponentMobility::Movable;
					Component->SetStaticMesh(Mesh);
					Component->SetRelativeRotation(ResourceRow->RelativeRotation);
					Component->SetRelativeScale3D(ResourceRow->RelativeScale);
					Component->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
					Component->SetCollisionResponseToAllChannels(ECR_Ignore);
					Component->SetCollisionObjectType(GameActorTrace);

					Component->RegisterComponent();
					IsOk = true;
				}
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
