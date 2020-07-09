#include "MapActor.h"

AMapActor::AMapActor()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");

	GroundMeshComponent = CreateDefaultSubobject<UInstancedStaticMeshComponent>("GroundMeshComponent");
	CloudMeshComponent = CreateDefaultSubobject<UInstancedStaticMeshComponent>("CloudMeshComponent");
	FenceMeshComponent = CreateDefaultSubobject<UInstancedStaticMeshComponent>("FenceMeshComponent");
	CityMeshComponent = CreateDefaultSubobject<UInstancedStaticMeshComponent>("CityMeshComponent");

	GroundMeshComponent->AttachToComponent(RootComponent,FAttachmentTransformRules::KeepRelativeTransform);
	CloudMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	FenceMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	CityMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);


}
void AMapActor::On_Init()
{

}
void AMapActor::On_Tick(float DeltaSeconds)
{

}
void AMapActor::On_Delete()
{

}
int32 AMapActor::AddInstance(const FVector& InLocation)
{
	int32 TemIndex = GroundMeshComponent->AddInstance(FTransform(InLocation));
	CloudMeshComponent->AddInstance(FTransform(InLocation +  ShowLocation));
	return std::move(TemIndex);
}
void AMapActor::SetCloudInstanceVisible(const int32 & InIndex, const bool & InIsVisible)
{
	FTransform TemTrans;
	CloudMeshComponent->GetInstanceTransform(InIndex, TemTrans);
	FVector PreLocation = TemTrans.GetLocation();
	PreLocation.Z = 0;
	TemTrans.SetLocation(PreLocation + (InIsVisible ? ShowLocation : HideLocation));
	CloudMeshComponent->UpdateInstanceTransform(InIndex, TemTrans);
}