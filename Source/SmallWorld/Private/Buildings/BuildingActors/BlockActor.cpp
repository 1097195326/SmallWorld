#include "BlockActor.h"
#include "CityActor.h"


ABlockActor::ABlockActor()
{
	GrassCentreDirtTile = "/Game/CastlePack/Meshes/SM_GrassCentreDirtTile";
	GrassFullDirtTiles = "/Game/CastlePack/Meshes/SM_GrassFullDirtTiles";
	GrassTile = "/Game/CastlePack/Meshes/SM_GrassTile";
	GrassToDirtEdgeTile = "/Game/CastlePack/Meshes/SM_GrassToDirtEdgeTile";
	GrassToDirtTile = "/Game/CastlePack/Meshes/SM_GrassToDirtTile";
	DirtTile = "/Game/CastlePack/Meshes/SM_DirtTile";

	mCity = nullptr;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	BaseMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMeshComponent"));
	BaseMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);


}
void ABlockActor::On_Init()
{
	FString TitlePath;
	if (mCity->IsInWorld())
	{
		TitlePath = GrassCentreDirtTile;
	}
	else
	{
		TitlePath = GrassTile;
	}
	UStaticMesh * mesh = LoadObject<UStaticMesh>(this, *TitlePath);
	BaseMeshComponent->SetStaticMesh(mesh);

	

}

void ABlockActor::SetTileType(BlockTitleType _type)
{
	mTitleType = _type;

}
BlockTitleType ABlockActor::GetTileType()
{
	return mTitleType;
}
void ABlockActor::SetOrientation(CityOrientation _orientation)
{
	mCityOrientation = _orientation; 
}
CityOrientation ABlockActor::GetOrientation()
{
	return mCityOrientation;
}
void ABlockActor::SetCity(ACityActor * _City)
{
	mCity = _City;
}
ACityActor * ABlockActor::GetCity()
{
	return mCity;
}
void ABlockActor::SetMesh()
{
	
}
void ABlockActor::InitData(BlockData * Data)
{
	mData = Data;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BlockMesh(TEXT(""));

	BaseMeshComponent->SetStaticMesh(BlockMesh.Object);

}
bool ABlockActor::IsInWorld()
{
	if (mCity)
	{
		mCity->IsInWorld();
	}
	return false;
}