#include "CityActor.h"


ACityActor::ACityActor()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
		
	BaseMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CityMeshComponent"));
	BaseMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	
	BaseMeshComponent->SetRelativeScale3D(FVector(0.1f));

}
void ACityActor::InitData(CityData * _data)
{
	mData = _data;
}
void ACityActor::On_Init()
{
	float CityXOffSet = mIndex.X * CitySize * TitleSize;
	float CityYOffSet = mIndex.Y * CitySize * TitleSize;

	for (int x = 0; x < CitySize; x++)
	{
		vector<ABlockActor *> BlockList;
		for (int y = 0; y < CitySize; y++)
		{
			FTransform trans(FVector(CityXOffSet + x * TitleSize + TitleSize * 0.5, CityYOffSet + y * TitleSize + TitleSize * 0.5, 0));
			ABlockActor * BlockActor = Cast<ABlockActor>(UGameplayStatics::BeginDeferredActorSpawnFromClass(SWI, ABlockActor::StaticClass(), trans));
			if (BlockActor)
			{
				BlockActor->SetIndex(FBuildingIndex(x, y));
				BlockActor->SetCity(this);
				UGameplayStatics::FinishSpawningActor(BlockActor, trans);
				BlockList.push_back(BlockActor);
			}
		}
		BlockMap.push_back(BlockList);
	}
	if (!IsInWorld())
	{
		const FString Mountain1 = "/Game/CastlePack/Meshes/SM_01_Moutain";
		const FString Mountain2 = "/Game/CastlePack/Meshes/SM_02_Moutain";

		UStaticMesh * mesh = LoadObject<UStaticMesh>(this, *Mountain1);
		BaseMeshComponent->SetStaticMesh(mesh);
	}
}
void ACityActor::On_Delete()
{

}
