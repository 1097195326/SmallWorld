#include "BlockActor.h"


ABlockActor::ABlockActor()
{
	GrassCentreDirtTile = "/Game/CastlePack/CastlePack/SM_GrassCentreDirtTile";
	GrassFullDirtTiles = "/Game/CastlePack/CastlePack/SM_GrassFullDirtTiles";
	GrassTile = "/Game/CastlePack/CastlePack/SM_GrassTile";
	GrassToDirtEdgeTile = "/Game/CastlePack/CastlePack/SM_GrassToDirtEdgeTile";
	GrassToDirtTile = "/Game/CastlePack/CastlePack/SM_GrassToDirtTile";
	DirtTile = "/Game/CastlePack/CastlePack/SM_DirtTile";

	RootComponent = BaseMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMeshComponent"));
	
//#ifdef ZHX_BUG
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BlockMesh(*GrassTile);
	BaseMeshComponent->SetStaticMesh(BlockMesh.Object);

//#endif // ZHX_BUG

}

void ABlockActor::InitData(BlockData * Data)
{
	mData = Data;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BlockMesh(TEXT(""));

	BaseMeshComponent->SetStaticMesh(BlockMesh.Object);

}
