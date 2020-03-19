#include "WoodStoneStoreActor.h"


AWoodStoneStoreActor::AWoodStoneStoreActor()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	BaseMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	BaseMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	
}
void AWoodStoneStoreActor::On_Init()
{
	
}
