#include "TowerActor.h"

ATowerActor::ATowerActor()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	BaseMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GateComponent"));
	BaseMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	mLevel = 1;
	mMaxLevel = 3;

	MeshPathLevel_1 = TEXT("/Game/CastlePack/Meshes/SM_Lvl1_Tower");
	MeshPathLevel_2 = TEXT("/Game/CastlePack/Meshes/SM_Lvl2_Tower");
	MeshPathLevel_3 = TEXT("/Game/CastlePack/Meshes/SM_Lvl3_Tower");

}
void ATowerActor::On_Init()
{
	UStaticMesh * mesh = LoadObject<UStaticMesh>(this, *GetMeshPath());
	if (mesh)
	{
		BaseMeshComponent->SetStaticMesh(mesh);
	}

}