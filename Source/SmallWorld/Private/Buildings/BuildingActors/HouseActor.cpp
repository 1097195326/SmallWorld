#include "HouseActor.h"


AHouseActor::AHouseActor()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	BaseMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	BaseMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	
	mMaxLevel = 3;

	MeshPathLevel_1 = TEXT("/Game/CastlePack/Meshes/SM_Hovel_Lvl1");
	MeshPathLevel_2 = TEXT("/Game/CastlePack/Meshes/SM_Hovel_Lvl2");
	MeshPathLevel_3 = TEXT("/Game/CastlePack/Meshes/SM_Hovel_Lvl3");
}
void AHouseActor::On_Init()
{
	mData->mLevel = 1;
	UStaticMesh * mesh = LoadObject<UStaticMesh>(this, *GetMeshPath());
	if (mesh)
	{
		BaseMeshComponent->SetStaticMesh(mesh);
	}
}
