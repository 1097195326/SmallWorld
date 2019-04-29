#include "MillActor.h"


AMillActor::AMillActor()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	BaseSkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComponent"));
	BaseSkeletalMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	
	mMaxLevel = 3;

	MeshPathLevel_0 = TEXT("/Game/CastlePack/Meshes/SK_Mill_Lvl0");
	MeshPathLevel_1 = TEXT("/Game/CastlePack/Meshes/SK_Mill_Lvl1");
	MeshPathLevel_2 = TEXT("/Game/CastlePack/Meshes/SK_Mill_Lvl2");
	MeshPathLevel_3 = TEXT("/Game/CastlePack/Meshes/SK_Mill_Lvl3");
}
void AMillActor::On_Init()
{
	mData->mLevel = 0;
	USkeletalMesh * mesh = LoadObject<USkeletalMesh>(this, *GetMeshPath());
	if (mesh)
	{
		BaseSkeletalMeshComponent->SetSkeletalMesh(mesh);
	}
}
