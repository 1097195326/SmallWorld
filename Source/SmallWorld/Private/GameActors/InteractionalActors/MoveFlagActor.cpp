#include "MoveFlagActor.h"
#include "GroundTileActor.h"




AMoveFlagActor::AMoveFlagActor()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");

	MeshComponent = CreateDefaultSubobject<UInstancedStaticMeshComponent>("MeshComponent");
	MeshComponent->SetWorldScale3D(FVector(2.5f));
	MeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	MeshComponent->SetCollisionObjectType(GameActorTrace);
	
	//0 : left: FVector(0, -60, 0)		FRotator(0, 90, 0)
	//1 : Forward : FVector(60, 0, 0)	FRotator(0, 180, 0)
	//2 : Right : FVector(0, 60, 0)		FRotator(0, -90, 0)
	//3 : Back : FVector(-60, 0, 0)		FRotator(0, 0, 0)
}
void AMoveFlagActor::On_Init()
{
	//ForwardMeshComponent->AddInstance()

}
void AMoveFlagActor::On_Tick(float DeltaSeconds)
{

}
void AMoveFlagActor::On_Delete()
{

}