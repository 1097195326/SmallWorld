#include "GateActor.h"


AGateActor::AGateActor()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	BaseSkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GateComponent"));
	BaseSkeletalMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	mLevel = 1;
	mMaxLevel = 3;

	MeshPathLevel_1 = TEXT("/Game/CastlePack/Meshes/SK_Lvl1_Gate");
	MeshPathLevel_2 = TEXT("/Game/CastlePack/Meshes/SK_Lvl2_Gate");
	MeshPathLevel_3 = TEXT("/Game/CastlePack/Meshes/SK_Lvl3_Gate");

}
void AGateActor::On_Init()
{

	USkeletalMesh * mesh = LoadObject<USkeletalMesh>(this, *GetMeshPath());
	if (mesh)
	{
		BaseSkeletalMeshComponent->SetSkeletalMesh(mesh);
		
	}
	if (mDirection != Dir_None)
	{
		BaseSkeletalMeshComponent->SetRelativeRotation(DirectionRotation() + FRotator(0.f,180.f,0.f));
	}
}
