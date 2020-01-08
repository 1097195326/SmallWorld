#include "StoneStoreActor.h"


AStoneStoreActor::AStoneStoreActor()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	BaseMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	BaseMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	
	mMaxLevel = 1;

	MeshPathLevel_1 = TEXT("/Game/CastlePack/Meshes/SM_Stockpile_Lvl1");
}
void AStoneStoreActor::On_Init()
{
	mData->BuildingLevel = 1;
	UStaticMesh * mesh = LoadObject<UStaticMesh>(this, *GetMeshPath());
	if (mesh)
	{
		BaseMeshComponent->SetStaticMesh(mesh);
	}
}
