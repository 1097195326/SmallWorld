#include "StoneStoreActor.h"


AStoneStoreActor::AStoneStoreActor()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	BaseMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GateComponent"));
	BaseMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	mLevel = 1;
	mMaxLevel = 1;

	MeshPathLevel_1 = TEXT("/Game/CastlePack/Meshes/SM_Stockpile_Lvl1");
}
void AStoneStoreActor::On_Init()
{
	UStaticMesh * mesh = LoadObject<UStaticMesh>(this, *GetMeshPath());
	if (mesh)
	{
		BaseMeshComponent->SetStaticMesh(mesh);
	}
}