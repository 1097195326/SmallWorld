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

	Anim0 = TEXT("/Game/CastlePack/Animations/A_Mill_Lvl0_Anim");
	Anim1 = TEXT("/Game/CastlePack/Animations/A_Mill_Lvl1_Anim");
	Anim2 = TEXT("/Game/CastlePack/Animations/A_Mill_Lvl2_Anim");
	Anim3 = TEXT("/Game/CastlePack/Animations/A_Mill_Lvl3_Anim");
}
void AMillActor::On_Init()
{
	mData->mLevel = 0;
	USkeletalMesh * mesh = LoadObject<USkeletalMesh>(this, *GetMeshPath());
	if (mesh)
	{
		BaseSkeletalMeshComponent->SetSkeletalMesh(mesh);
		BaseSkeletalMeshComponent->SetAnimationMode(EAnimationMode::AnimationSingleNode);
		
		UAnimationAsset * AnimAsset = LoadObject<UAnimationAsset>(this, *GetAnimPath());
		if (AnimAsset)
		{
			BaseSkeletalMeshComponent->PlayAnimation(AnimAsset, true);
		}
	}
}
FString AMillActor::GetAnimPath()
{
	FString AnimPath;
	switch (mData->mLevel)
	{
	case 0:
		AnimPath = Anim0;
		break;
	case 1:
		AnimPath = Anim1;
		break;
	case  2:
		AnimPath = Anim2;
		break;
	case  3:
		AnimPath = Anim3;
		break;
	}
	return AnimPath;
}
