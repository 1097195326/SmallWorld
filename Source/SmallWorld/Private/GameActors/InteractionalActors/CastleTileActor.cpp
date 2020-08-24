#include "CastleTileActor.h"




ACastleTileActor::ACastleTileActor()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");

	CastleTileComponent = CreateDefaultSubobject<UStaticMeshComponent>("CastleTileComponent");
	CollisionBoxComponent = CreateDefaultSubobject<UBoxComponent>("CollisionBoxComponent");

	CastleTileComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	CollisionBoxComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);


}
void ACastleTileActor::On_Init()
{


}
void ACastleTileActor::On_Tick(float DeltaSeconds)
{

}
void ACastleTileActor::On_Delete()
{

}
void ACastleTileActor::TrackAround()
{

}