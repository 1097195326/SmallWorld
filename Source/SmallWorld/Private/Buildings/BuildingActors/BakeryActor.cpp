#include "BakeryActor.h"




ABakeryActor::ABakeryActor()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	BaseMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GateComponent"));
	BaseMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	mLevel = 0;
	mMaxLevel = 3;

	MeshPathLevel_0 = TEXT("/Game/CastlePack/Meshes/SM_Bakery_Lvl0");
	MeshPathLevel_1 = TEXT("/Game/CastlePack/Meshes/SM_Bakery_Lvl1");
	MeshPathLevel_2 = TEXT("/Game/CastlePack/Meshes/SM_Bakery_Lvl2");
	MeshPathLevel_3 = TEXT("/Game/CastlePack/Meshes/SM_Bakery_Lvl3");
}
void ABakeryActor::On_Init()
{
	UStaticMesh * mesh = LoadObject<UStaticMesh>(this, *GetMeshPath());
	if (mesh)
	{
		BaseMeshComponent->SetStaticMesh(mesh);
	}
}