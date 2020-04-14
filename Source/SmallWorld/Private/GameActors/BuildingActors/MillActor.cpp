#include "MillActor.h"


AMillActor::AMillActor()
{
	
	
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

TSharedPtr<SWidget>	AMillActor::CreateActorDetailWidget()
{
	return SNullWidget::NullWidget;
}