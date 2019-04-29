#include "CommandCenterActor.h"




ACommandCenterActor::ACommandCenterActor()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	BaseMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	BaseMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	
	mMaxLevel = 3;

	MeshPathLevel_0 = TEXT("/Game/CastlePack/Meshes/SM_Keep_Lvl0");
	MeshPathLevel_1 = TEXT("/Game/CastlePack/Meshes/SM_Keep_Lvl1");
	MeshPathLevel_2 = TEXT("/Game/CastlePack/Meshes/SM_Keep_Lvl2");
	MeshPathLevel_3 = TEXT("/Game/CastlePack/Meshes/SM_Keep_Lvl3");

}
void ACommandCenterActor::On_Init()
{
	mData->mLevel = 0;
	UStaticMesh * mesh = LoadObject<UStaticMesh>(this, *GetMeshPath());
	if (mesh)
	{
		BaseMeshComponent->SetStaticMesh(mesh);
	}
}
