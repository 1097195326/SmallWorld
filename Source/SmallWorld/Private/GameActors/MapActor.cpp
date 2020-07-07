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