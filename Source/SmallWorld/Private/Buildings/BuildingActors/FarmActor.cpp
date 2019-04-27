#include "FarmActor.h"




AFarmActor::AFarmActor()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	BaseMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GateComponent"));
	BaseMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	mData->mLevel = 1;
	mMaxLevel = 3;

	MeshPathLevel_1 = TEXT("/Game/CastlePack/Meshes/SM_Wheatfarm_Lvl1");
	MeshPathLevel_2 = TEXT("/Game/CastlePack/Meshes/SM_Wheatfarm_Lvl2");
	MeshPathLevel_3 = TEXT("/Game/CastlePack/Meshes/SM_Wheatfarm_Lvl3");
}
void AFarmActor::On_Init()
{
	UStaticMesh * mesh = LoadObject<UStaticMesh>(this, *GetMeshPath());
	if (mesh)
	{
		BaseMeshComponent->SetStaticMesh(mesh);
	}
}
