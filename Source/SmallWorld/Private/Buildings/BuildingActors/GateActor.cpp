#include "GateActor.h"


AGateActor::AGateActor()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	BaseMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GateComponent"));
	BaseMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	mLevel = 1;
	mMaxLevel = 3;

	MeshPathLevel_1 = TEXT("/Game/CastlePack/Meshes/SK_Lvl1_Gate");
	MeshPathLevel_2 = TEXT("/Game/CastlePack/Meshes/SK_Lvl2_Gate");
	MeshPathLevel_3 = TEXT("/Game/CastlePack/Meshes/SK_Lvl3_Gate");

}
void AGateActor::On_Init()
{

	UStaticMesh * mesh = LoadObject<UStaticMesh>(this, *GetMeshPath());
	if (mesh)
	{
		BaseMeshComponent->SetStaticMesh(mesh);
	}

}
