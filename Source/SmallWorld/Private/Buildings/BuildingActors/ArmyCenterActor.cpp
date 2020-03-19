#include "ArmyCenterActor.h"
#include "ArmyCenterData.h"



AArmyCenterActor::AArmyCenterActor()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	BaseMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	BaseMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);


}
void AArmyCenterActor::On_Init()
{
	
}
