#include "MillActor.h"


AMillActor::AMillActor()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	BaseMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GateComponent"));
	BaseMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	mLevel = 0;
	mMaxLevel = 3;

	MeshPathLevel_1 = TEXT("/Game/CastlePack/Meshes/SK_Mill_Lvl0");
	MeshPathLevel_1 = TEXT("/Game/CastlePack/Meshes/SK_Mill_Lvl1");
	MeshPathLevel_2 = TEXT("/Game/CastlePack/Meshes/SK_Mill_Lvl2");
	MeshPathLevel_3 = TEXT("/Game/CastlePack/Meshes/SK_Mill_Lvl3");
}
void AMillActor::On_Init()
{
	UStaticMesh * mesh = LoadObject<UStaticMesh>(this, *GetMeshPath());
	if (mesh)
	{
		BaseMeshComponent->SetStaticMesh(mesh);
	}
}