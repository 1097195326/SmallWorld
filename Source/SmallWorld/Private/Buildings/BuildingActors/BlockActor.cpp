#include "BlockActor.h"
#include "CityActor.h"


ABlockActor::ABlockActor()
{
	GrassTile = "/Game/CastlePack/Meshes/SM_GrassTile_1";
	GrassToDirtTile = "/Game/CastlePack/Meshes/SM_GrassTile_2";
	GrassToDirtEdgeTile = "/Game/CastlePack/Meshes/SM_GrassTile_3";
	GrassFullDirtTiles = "/Game/CastlePack/Meshes/SM_GrassTile_4";
	GrassCentreDirtTile = "/Game/CastlePack/Meshes/SM_GrassTile_5";
	DirtTile = "/Game/CastlePack/Meshes/SM_GrassTile_6";

	mCity = nullptr;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	BaseMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMeshComponent"));
	BaseMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);


}
void ABlockActor::On_Init()
{
	FString TitlePath = GetMeshPath();
	
	UStaticMesh * mesh = LoadObject<UStaticMesh>(this, *TitlePath);
	BaseMeshComponent->SetStaticMesh(mesh);
	if (mData->mDirection != Dir_None)
	{
		BaseMeshComponent->SetRelativeRotation(DirectionRotation());
	}
}
FString ABlockActor::GetMeshPath()
{
	FString tileStr = GrassTile;
	if (IsInWorld())
	{
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
			if (mData->mIndex.X == 0 && mData->mIndex.Y == 0)
			{
				tileStr = GrassToDirtEdgeTile;
				SetDirection(Dir_Corner_City_LeftBottom);
			}
			else if (mData->mIndex.X == CitySize - 1 && mData->mIndex.Y == 0)
			{
				tileStr = GrassToDirtEdgeTile;
				SetDirection(Dir_Corner_City_LeftTop);
			}
			else if (mData->mIndex.X == CitySize - 1 && mData->mIndex.Y == CitySize - 1)
			{
				tileStr = GrassToDirtEdgeTile;
				SetDirection(Dir_Corner_City_RightTop);
			}
			else if (mData->mIndex.X == 0 && mData->mIndex.Y == CitySize - 1)
			{
				tileStr = GrassToDirtEdgeTile;
				SetDirection(Dir_Corner_City_RightBottom);
			}
			else if (mData->mIndex.Y == 0)
			{
				tileStr = GrassToDirtTile;
				SetDirection(Dir_CityEdge_Left);
			}
			else if (mData->mIndex.Y == CitySize - 1)
			{
				tileStr = GrassToDirtTile;
				SetDirection(Dir_CityEdge_Right);
			}
			else if (mData->mIndex.X == 0)
			{
				tileStr = GrassToDirtTile;
				SetDirection(Dir_CityEdge_Bottom);
			}
			else if (mData->mIndex.X == CitySize - 1)
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
			tileStr = GrassFullDirtTiles;
			break;
		case CornerCastle_LeftBottom:
		case CornerCastle_LeftTop:
		case CornerCastle_RightBottom:
		case CornerCastle_RightTop:
		case CenterCastle_Left:
		case CenterCastle_Right:
		case CenterCastle_Top:
		case CenterCastle_Bottom:
		{
			const int OutCastleSize = (CitySize - CastleSize) * 0.5;

			if (mData->mIndex.X == OutCastleSize && mData->mIndex.Y == OutCastleSize)
			{
				tileStr = GrassToDirtEdgeTile;
				SetDirection(Dir_Corner_Castle_LeftBottom);
			}
			else if (mData->mIndex.X == CitySize - OutCastleSize - 1 && mData->mIndex.Y == OutCastleSize)
			{
				tileStr = GrassToDirtEdgeTile;
				SetDirection(Dir_Corner_Castle_LeftTop);
			}
			else if (mData->mIndex.X == CitySize - OutCastleSize - 1 && mData->mIndex.Y == CitySize - OutCastleSize - 1)
			{
				tileStr = GrassToDirtEdgeTile;
				SetDirection(Dir_Corner_Castle_RightTop);
			}
			else if (mData->mIndex.X == OutCastleSize && mData->mIndex.Y == CitySize - OutCastleSize - 1)
			{
				tileStr = GrassToDirtEdgeTile;
				SetDirection(Dir_Corner_Castle_RightBottom);
			}
			else if (mData->mIndex.Y == OutCastleSize)
			{
				tileStr = GrassToDirtTile;
				SetDirection(Dir_CastleEdge_Left);
			}
			else if (mData->mIndex.Y == CitySize - OutCastleSize - 1)
			{
				tileStr = GrassToDirtTile;
				SetDirection(Dir_CastleEdge_Right);
			}
			else if (mData->mIndex.X == OutCastleSize)
			{
				tileStr = GrassToDirtTile;
				SetDirection(Dir_CastleEdge_Bottom);
			}
			else if (mData->mIndex.X == CitySize - OutCastleSize - 1)
			{
				tileStr = GrassToDirtTile;
				SetDirection(Dir_CastleEdge_Top);
			}
			else
			{
				tileStr = GrassTile;
			}
		}
		break;
		case Center_City:
			tileStr = GrassFullDirtTiles;
			break;
		case CenterOfCenter_City:
			tileStr = GrassCentreDirtTile;
			break;
		default:
			tileStr = GrassTile;
			break;
		}
	}
	return tileStr;
}
//void ABlockActor::InitData(BlockData * Data)
//{
//    mData = Data;
//    static ConstructorHelpers::FObjectFinder<UStaticMesh> BlockMesh(TEXT(""));
//
//    BaseMeshComponent->SetStaticMesh(BlockMesh.Object);
//
//}
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
		return mCity->IsInWorld();
	}
	return false;
}
