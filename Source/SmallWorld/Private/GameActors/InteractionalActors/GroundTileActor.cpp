#include "GroundTileActor.h"




AGroundTileActor::AGroundTileActor()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");

	GroundTileComponent = CreateDefaultSubobject<UStaticMeshComponent>("GroundTileComponent");
	CloudTileComponent = CreateDefaultSubobject<UStaticMeshComponent>("CloudTileComponent");
	CollisionBoxComponent = CreateDefaultSubobject<UBoxComponent>("CollisionBoxComponent");

	GroundTileComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	CloudTileComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	CollisionBoxComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);


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
void AGroundTileActor::TrackAround()
{
	UWorld * wd = GetWorld();



}