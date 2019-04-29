#include "WallActor.h"


AWallActor::AWallActor()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	BaseMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	BaseMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	
	mMaxLevel = 3;

	MeshPathLevel_1 = TEXT("/Game/CastlePack/Meshes/SM_Lvl1_Wall");
	MeshPathLevel_2 = TEXT("/Game/CastlePack/Meshes/SM_Lvl2_Wall");
	MeshPathLevel_3 = TEXT("/Game/CastlePack/Meshes/SM_Lvl3_Wall");
}
void AWallActor::On_Init()
{
	mData->mLevel = 1;
	UStaticMesh * mesh = LoadObject<UStaticMesh>(this, *GetMeshPath());
	if (mesh)
	{
		BaseMeshComponent->SetStaticMesh(mesh);
	}
	if (mData->mDirection != Dir_None)
	{
		BaseMeshComponent->SetRelativeRotation(DirectionRotation() + FRotator(0.f, -90.f, 0.f));
	}
}
