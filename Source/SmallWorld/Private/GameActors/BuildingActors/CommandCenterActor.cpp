#include "CommandCenterActor.h"
#include "SCommandCenter.h"
#include "GameDataManager.h"


ACommandCenterActor::ACommandCenterActor()
{
	

}
void ACommandCenterActor::On_Init()
{
	
}
TSharedPtr<SWidget>	ACommandCenterActor::CreateActorDetailWidget()
{
	SAssignNew(ActorWidget, SCommandCenter)
		.CommandCenterData((CommandCenterDataClass*)BuildingData);

	return ActorWidget;
}
void ACommandCenterActor::RefreshView()
{
	ActorWidget.IsValid() ? ActorWidget->RefreshView() : NULL;

}
bool ACommandCenterActor::SetMeshComponentByIconName(const FString& InIconName)
{
	bool IsOk = false;
	//FString MeshName = FString::Printf(TEXT("Mesh%s0"), *InIconName);
	FAssetData MeshData = GameDataManager::GetInstance()->GetBuildingAssetDataByIconName(InIconName);

	UStaticMesh* Mesh = Cast<UStaticMesh>(MeshData.GetAsset());
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
			Component->SetRelativeScale3D(FVector(0.5f));
			Component->RegisterComponent();
			IsOk = true;
		}
	}
	
	return IsOk;
}