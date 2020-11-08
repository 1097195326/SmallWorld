#include "MoveFlagActor.h"
#include "GroundTileActor.h"




AMoveFlagActor::AMoveFlagActor()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");

	MeshComponent = CreateDefaultSubobject<UInstancedStaticMeshComponent>("MeshComponent");
	MeshComponent->SetWorldScale3D(FVector(2.5f));
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	MeshComponent->SetCollisionObjectType(ECC_Visibility);
	MeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	//0 : left: FVector(0, -60, 0) FRotator(0, 0, 90)
	//1 : Forward : FVector(60, 0, 0) FRotator(0, 0, 180)
	//2 : Right : FVector(0, 60, 0) FRotator(0, 0, -90)
	//3 : Back : FVector(-60, 0, 0) FRotator(0, 0, 0)
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