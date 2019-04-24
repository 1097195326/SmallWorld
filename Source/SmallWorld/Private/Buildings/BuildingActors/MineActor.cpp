#include "MineActor.h"



AMineActor::AMineActor()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	BaseMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GateComponent"));
	BaseMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	mLevel = 0;
	mMaxLevel = 3;

	MeshPathLevel_0 = TEXT("/Game/CastlePack/Meshes/SM_Mine_lvl0");
	MeshPathLevel_1 = TEXT("/Game/CastlePack/Meshes/SM_Mine_lvl1");
	MeshPathLevel_2 = TEXT("/Game/CastlePack/Meshes/SM_Mine_lvl2");
	MeshPathLevel_3 = TEXT("/Game/CastlePack/Meshes/SM_Mine_lvl3");
}
void AMineActor::On_Init()
{
	UStaticMesh * mesh = LoadObject<UStaticMesh>(this, *GetMeshPath());
	if (mesh)
	{
		BaseMeshComponent->SetStaticMesh(mesh);
	}
}