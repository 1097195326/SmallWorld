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

	RootComponent = BaseMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMeshComponent"));
	
//#ifdef ZHX_BUG
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BlockMesh(*GrassCentreDirtTile);
	BaseMeshComponent->SetStaticMesh(BlockMesh.Object);
//#endif // ZHX_BUG

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