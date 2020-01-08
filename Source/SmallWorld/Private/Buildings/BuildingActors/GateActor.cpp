#include "GateActor.h"


AGateActor::AGateActor()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	BaseSkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComponent"));
	BaseSkeletalMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	
	mMaxLevel = 3;

	MeshPathLevel_1 = TEXT("/Game/CastlePack/Meshes/SK_Lvl1_Gate");
	MeshPathLevel_2 = TEXT("/Game/CastlePack/Meshes/SK_Lvl2_Gate");
	MeshPathLevel_3 = TEXT("/Game/CastlePack/Meshes/SK_Lvl3_Gate");

}
void AGateActor::On_Init()
{
	mData->BuildingLevel = 1;
	USkeletalMesh * mesh = LoadObject<USkeletalMesh>(this, *GetMeshPath());
	if (mesh)
	{
		BaseSkeletalMeshComponent->SetSkeletalMesh(mesh);
		
	}
	
}
