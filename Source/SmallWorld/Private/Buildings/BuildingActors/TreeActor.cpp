#include "TreeActor.h"

ATreeActor::ATreeActor()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	BaseMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	BaseMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	
	mMaxLevel = 3;

	MeshPathLevel_1 = TEXT("/Game/CastlePack/Meshes/SM_Tree1");
	MeshPathLevel_2 = TEXT("/Game/CastlePack/Meshes/SM_Tree2");
	MeshPathLevel_3 = TEXT("/Game/CastlePack/Meshes/SM_Tree3");
}
void ATreeActor::On_Init()
{
	mData->mLevel = 1;
	UStaticMesh * mesh = LoadObject<UStaticMesh>(this, *GetMeshPath());
	if (mesh)
	{
		BaseMeshComponent->SetStaticMesh(mesh);
	}
}
