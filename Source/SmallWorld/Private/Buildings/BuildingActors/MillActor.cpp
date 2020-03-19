#include "MillActor.h"


AMillActor::AMillActor()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	BaseSkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComponent"));
	BaseSkeletalMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	
}
void AMillActor::On_Init()
{
	//mData->BuildingLevel = 0;
	//USkeletalMesh * mesh;// = LoadObject<USkeletalMesh>(this, *GetMeshPath());
	//if (mesh)
	//{
	//	BaseSkeletalMeshComponent->SetSkeletalMesh(mesh);
	//	BaseSkeletalMeshComponent->SetAnimationMode(EAnimationMode::AnimationSingleNode);
	//	
	//	UAnimationAsset * AnimAsset = LoadObject<UAnimationAsset>(this, TEXT(""));
	//	if (AnimAsset)
	//	{
	//		BaseSkeletalMeshComponent->PlayAnimation(AnimAsset, true);
	//	}
	//}
}

