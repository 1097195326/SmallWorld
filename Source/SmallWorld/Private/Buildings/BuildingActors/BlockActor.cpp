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
		TitlePath = GetTileString();
	}
	else
	{
		TitlePath = GrassTile;
	}
	UStaticMesh * mesh = LoadObject<UStaticMesh>(this, *TitlePath);
	BaseMeshComponent->SetStaticMesh(mesh);
	if (mDirection != Dir_None)
	{
		BaseMeshComponent->SetRelativeRotation(DirectionRotation());
	}
}
FString ABlockActor::GetTileString()
{
	FString tileStr;
	switch (mCityOrientation)
	{
	case O_None:
	case CornerOutControll_LeftBottom:
	case CornerOutControll_LeftTop:
	case CornerOutControll_RightBottom:
	case CornerOutControll_RightTop:
	case CenterOutControll_Left:
	case CenterOutControll_Right:
	case CenterOutControll_Top:
	case CenterOutControll_Bottom:
	case OutSkirtOutControll_LeftBottom:
	case OutSkirtOutControll_LeftTop:
	case OutSkirtOutControll_RightBottom:
	case OutSkirtOutControll_RightTop:
	case OutSkirtOutControll_TopLeft:
	case OutSkirtOutControll_TopRight:
	case OutSkirtOutControll_BottomLeft:
	case OutSkirtOutControll_BottomRight:
	case FarmOutControll_LeftBottom:
	case FarmOutControll_LeftTop:
	case FarmOutControll_RightBottom:
	case FarmOutControll_RightTop:
	case FarmOutControll_TopLeft:
	case FarmOutControll_TopRight:
	case FarmOutControll_BottomLeft:
	case FarmOutControll_BottomRight:
	{
		if (mIndex.X == 0 && mIndex.Y == 0)
		{
			tileStr = GrassToDirtEdgeTile;
			SetDirection(Dir_Corner_City_LeftBottom);
		}
		else if (mIndex.X == CitySize - 1 && mIndex.Y == 0)
		{
			tileStr = GrassToDirtEdgeTile;
			SetDirection(Dir_Corner_City_LeftTop);
		}
		else if (mIndex.X == CitySize - 1 && mIndex.Y == CitySize - 1)
		{
			tileStr = GrassToDirtEdgeTile;
			SetDirection(Dir_Corner_City_RightTop);
		}
		else if (mIndex.X == 0 && mIndex.Y == CitySize - 1)
		{
			tileStr = GrassToDirtEdgeTile;
			SetDirection(Dir_Corner_City_RightBottom);
		}
		else if (mIndex.Y == 0)
		{
			tileStr = GrassToDirtTile;
			SetDirection(Dir_CityEdge_Left);
		}
		else if (mIndex.Y == CitySize - 1)
		{
			tileStr = GrassToDirtTile;
			SetDirection(Dir_CityEdge_Right);
		}
		else if (mIndex.X == 0)
		{
			tileStr = GrassToDirtTile;
			SetDirection(Dir_CityEdge_Bottom);
		}
		else if (mIndex.X == CitySize - 1)
		{
			tileStr = GrassToDirtTile;
			SetDirection(Dir_CityEdge_Top);
		}
		else
		{
			tileStr = GrassTile;
		}
	}
		break;
	case CornerControll_LeftBottom:
	case CornerControll_LeftTop:
	case CornerControll_RightBottom:
	case CornerControll_RightTop:
		tileStr = GrassCentreDirtTile;
		break;
	case CenterControll_Left:
	case CenterControll_Right:
	case CenterControll_Top:
	case CenterControll_Bottom:
		tileStr = DirtTile;
		break;
	case FarmControll_LeftBottom:
	case FarmControll_LeftTop:
	case FarmControll_RightBottom:
	case FarmControll_RightTop:
	case FarmControll_TopLeft:
	case FarmControll_TopRight:
	case FarmControll_BottomLeft:
	case FarmControll_BottomRight:
	case CornerCastle_LeftBottom:
	case CornerCastle_LeftTop:
	case CornerCastle_RightBottom:
	case CornerCastle_RightTop:
		tileStr = GrassFullDirtTiles;
		break;
	case CenterCastle_Left:
	case CenterCastle_Right:
	case CenterCastle_Top:
	case CenterCastle_Bottom:
		tileStr = DirtTile;
		break;
	case CityCenter:
	case CenterOfCenter:
		tileStr = GrassCentreDirtTile;
		break;
	default:
		tileStr = GrassTile;
		break;
	}

	return tileStr;
}
void ABlockActor::InitData(BlockData * Data)
{
	mData = Data;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BlockMesh(TEXT(""));

	BaseMeshComponent->SetStaticMesh(BlockMesh.Object);

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
bool ABlockActor::IsInWorld()
{
	if (mCity)
	{
		mCity->IsInWorld();
	}
	return false;
}