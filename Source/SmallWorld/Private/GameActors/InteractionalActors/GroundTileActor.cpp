#include "GroundTileActor.h"




AGroundTileActor::AGroundTileActor()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");

	GroundTileComponent = CreateDefaultSubobject<UStaticMeshComponent>("GroundTileComponent");
	CloudTileComponent = CreateDefaultSubobject<UStaticMeshComponent>("CloudTileComponent");

	GroundTileComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	CloudTileComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);



}
void AGroundTileActor::On_Init()
{

}
void AGroundTileActor::On_Tick(float DeltaSeconds)
{

}
void AGroundTileActor::On_Delete()
{

}