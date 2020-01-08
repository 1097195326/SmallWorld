#include "FoodStoreActor.h"



AFoodStoreActor::AFoodStoreActor()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	BaseMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	BaseMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	
	mMaxLevel = 3;

	MeshPathLevel_0 = TEXT("/Game/CastlePack/Meshes/Stock_SM_Wheat_0");
	MeshPathLevel_1 = TEXT("/Game/CastlePack/Meshes/Stock_SM_Wheat_1");
	MeshPathLevel_2 = TEXT("/Game/CastlePack/Meshes/Stock_SM_Wheat_2");
	MeshPathLevel_3 = TEXT("/Game/CastlePack/Meshes/Stock_SM_Wheat_3");
}
void AFoodStoreActor::On_Init()
{
	mData->BuildingLevel = 0;
	UStaticMesh * mesh = LoadObject<UStaticMesh>(this, *GetMeshPath());
	if (mesh)
	{
		BaseMeshComponent->SetStaticMesh(mesh);
	}
}
