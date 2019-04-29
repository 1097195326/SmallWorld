#include "MoneyStoreActor.h"



AMoneyStoreActor::AMoneyStoreActor()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	BaseMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	BaseMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	
	mMaxLevel = 3;

	MeshPathLevel_1 = TEXT("/Game/CastlePack/Meshes/SM_Treasurey_1");
	MeshPathLevel_2 = TEXT("/Game/CastlePack/Meshes/SM_Treasurey_2");
	MeshPathLevel_3 = TEXT("/Game/CastlePack/Meshes/SM_Treasurey_3");
}
void AMoneyStoreActor::On_Init()
{
	mData->mLevel = 1;
	UStaticMesh * mesh = LoadObject<UStaticMesh>(this, *GetMeshPath());
	if (mesh)
	{
		BaseMeshComponent->SetStaticMesh(mesh);
	}
}
