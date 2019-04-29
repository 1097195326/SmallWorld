#include "StoneActor.h"


AStoneActor::AStoneActor()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	BaseMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	BaseMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	
	mMaxLevel = 3;

	MeshPathLevel_1 = TEXT("/Game/CastlePack/Meshes/SM_Rock1");
	MeshPathLevel_2 = TEXT("/Game/CastlePack/Meshes/SM_Rock2");
	MeshPathLevel_3 = TEXT("/Game/CastlePack/Meshes/SM_Rock3");
}
void AStoneActor::On_Init()
{
	mData->mLevel = 1;
	UStaticMesh * mesh = LoadObject<UStaticMesh>(this, *GetMeshPath());
	if (mesh)
	{
		BaseMeshComponent->SetStaticMesh(mesh);
	}
}
