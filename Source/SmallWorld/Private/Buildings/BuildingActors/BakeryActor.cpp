#include "BakeryActor.h"
#include "BakeryData.h"



ABakeryActor::ABakeryActor()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	BaseMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	BaseMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	
}
void ABakeryActor::On_Init()
{
	
}
