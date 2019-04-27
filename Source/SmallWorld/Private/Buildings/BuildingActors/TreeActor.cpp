#include "TreeActor.h"

ATreeActor::ATreeActor()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	BaseMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GateComponent"));
	BaseMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	mData->mLevel = 1;
	mMaxLevel = 3;

	MeshPathLevel_1 = TEXT("/Game/CastlePack/Meshes/SM_Tree1");
	MeshPathLevel_2 = TEXT("/Game/CastlePack/Meshes/SM_Tree2");
	MeshPathLevel_3 = TEXT("/Game/CastlePack/Meshes/SM_Tree3");
}
void ATreeActor::On_Init()
{
	UStaticMesh * mesh = LoadObject<UStaticMesh>(this, *GetMeshPath());
	if (mesh)
	{
		BaseMeshComponent->SetStaticMesh(mesh);
	}
}
