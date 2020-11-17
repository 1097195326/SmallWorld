#include "TargetFlagActor.h"
#include "GroundTileActor.h"




ATargetFlagActor::ATargetFlagActor()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	MeshComponent->SetWorldScale3D(FVector(2.5f));
	MeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	MeshComponent->SetCollisionObjectType(GameActorTrace);
	
}
void ATargetFlagActor::On_Init()
{


}
void ATargetFlagActor::On_Tick(float DeltaSeconds)
{

}
void ATargetFlagActor::On_Delete()
{

}