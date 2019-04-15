#include "BlockActor.h"
#include "PieceMeshComponent.h"

ABlockActor::ABlockActor()
{
	GrassCentreDirtTile = "/Game/CastlePack/Meshes/SM_GrassCentreDirtTile";
	GrassFullDirtTiles = "/Game/CastlePack/Meshes/SM_GrassFullDirtTiles";
	GrassTile = "/Game/CastlePack/Meshes/SM_GrassTile";
	GrassToDirtEdgeTile = "/Game/CastlePack/Meshes/SM_GrassToDirtEdgeTile";
	GrassToDirtTile = "/Game/CastlePack/Meshes/SM_GrassToDirtTile";
	DirtTile = "/Game/CastlePack/Meshes/SM_DirtTile";

	RootComponent = BaseMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMeshComponent"));
	
//#ifdef ZHX_BUG
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BlockMesh(TEXT("/Game/CastlePack/Meshes/SM_GrassTile"));
	BaseMeshComponent->SetStaticMesh(BlockMesh.Object);
//#endif // ZHX_BUG

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
