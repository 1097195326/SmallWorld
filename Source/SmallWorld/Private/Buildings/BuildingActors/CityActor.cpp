#include "CityActor.h"


ACityActor::ACityActor()
{
	RootComponent = CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetHiddenInGame(false);
	CollisionBox->ShapeColor = FColor(0,255,0,255);

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
	float CityExtent = CitySize * TitleSize * 0.5f;
	CollisionBox->SetBoxExtent(FVector(CityExtent, CityExtent, CityExtent));

	// build City Map
	const float CityXOffSet = mIndex.X * CitySize * TitleSize;
	const float CityYOffSet = mIndex.Y * CitySize * TitleSize;

	for (int x = 0; x < CitySize; x++)
	{
		vector<ABlockActor *> BlockList;
		for (int y = 0; y < CitySize; y++)
		{
			FTransform trans(FVector(CityXOffSet + x * TitleSize + TitleSize * 0.5, CityYOffSet + y * TitleSize + TitleSize * 0.5, 0));
			ABlockActor * BlockActor = Cast<ABlockActor>(UGameplayStatics::BeginDeferredActorSpawnFromClass(SWI, ABlockActor::StaticClass(), trans));
			if (BlockActor)
			{
				BlockActor->SetCity(this);
				BlockActor->SetIndex(FBuildingIndex(x, y));
				if (IsInWorld())
				{
					BlockActor->SetOrientation(CalCulateOrientation(x, y));

				}
				BlockList.push_back(BlockActor);
				UGameplayStatics::FinishSpawningActor(BlockActor, trans);
			}
		}
		BlockMap.push_back(BlockList);
	}
	
	// build castle wall
	const int OutCastleSize = (CitySize - CastleSize) * 0.5;
	const float CastleWallXOffSet = mIndex.X * CitySize * TitleSize + TitleSize * OutCastleSize + TitleSize * 0.5;
	const float CastleWallYOffSet = mIndex.Y * CitySize * TitleSize + TitleSize * OutCastleSize + TitleSize * 0.5;
	const float CastleWallLength = TitleSize * (CastleSize - 1);
	for (int i = 0; i < 4; i++)
	{
		BuildingDirection Dir;
		FVector DirV;
		FVector Origin;
		if (i == 0)
		{
			Origin = FVector(CastleWallXOffSet, CastleWallYOffSet, 0);
			DirV = FVector(1,0,0);
			Dir = Dir_CastleEdge_Left;
		}else if (i == 1)
		{
			Origin = FVector(CastleWallXOffSet + CastleWallLength, CastleWallYOffSet, 0);
			DirV = FVector(0, 1, 0);
			Dir = Dir_CastleEdge_Top;
		}else if (i ==2)
		{
			Origin = FVector(CastleWallXOffSet + CastleWallLength, CastleWallYOffSet + CastleWallLength, 0);
			DirV = FVector(-1, 0, 0);
			Dir = Dir_CastleEdge_Right;
		}else if (i ==3)
		{
			Origin = FVector(CastleWallXOffSet, CastleWallYOffSet + CastleWallLength, 0);
			DirV = FVector(0, -1, 0);
			Dir = Dir_CastleEdge_Bottom;
		}
		for (int j = 0;j < (int)(CastleWallLength / WallSize); j++)
		{
			FTransform trans(Origin + DirV * WallSize * j);
			ABaseBuildingActor * BuildingActor = nullptr;
			if (j == 0)
			{
				BuildingActor = Cast<ATowerActor>(UGameplayStatics::BeginDeferredActorSpawnFromClass(SWI, ATowerActor::StaticClass(), trans));
			}else if (j == (int)CastleWallLength / WallSize / 2)
			{
				BuildingActor = Cast<AGateActor>(UGameplayStatics::BeginDeferredActorSpawnFromClass(SWI, AGateActor::StaticClass(), trans));
			}else
			{
				BuildingActor = Cast<AWallActor>(UGameplayStatics::BeginDeferredActorSpawnFromClass(SWI, AWallActor::StaticClass(), trans));
			}
			if (BuildingActor)
			{
				BuildingActor->SetDirection(Dir);
				UGameplayStatics::FinishSpawningActor(BuildingActor, trans);
			}
		}
	}
	// Bild City Bound Moutain
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
CityOrientation ACityActor::CalCulateOrientation(int _x, int _y)
{
	// OutControll 
	const int OutControllSize = (CitySize - CastleControllSize) * 0.5;
	const int OutCastleSize = (CitySize - CastleSize) * 0.5;
	const int OutCenterSize = (CitySize - CastleCenterSize) * 0.5;

	if (_x <  OutControllSize && _y < OutControllSize)
	{
		return CornerOutControll_LeftBottom;
	}else if (_x >= (CitySize - OutControllSize) && _y < OutControllSize)
	{
		return CornerOutControll_LeftTop;
	}else if (_x <  OutControllSize && _y >= (CitySize - OutControllSize))
	{
		return CornerOutControll_RightBottom;
	}else if (_x >= (CitySize - OutControllSize) && _y >= (CitySize - OutControllSize))
	{
		return CornerOutControll_RightTop;
	}else if ( _x >= OutCenterSize && _x < (CitySize - OutCenterSize) && _y < OutControllSize)
	{
		return CenterOutControll_Left;
	}else if (_x >= OutCenterSize && _x < (CitySize - OutCenterSize) && _y >= (CitySize - OutControllSize))
	{
		return CenterOutControll_Right;
	}else if (_y >= OutCenterSize && _y < (CitySize - OutCenterSize) && _x >= (CitySize - OutControllSize))
	{
		return CenterOutControll_Top;
	}else if (_y >= OutCenterSize && _y < (CitySize - OutCenterSize) && _x  < OutControllSize)
	{
		return CenterOutControll_Bottom;
	}else if (_x >= OutControllSize && _x < OutCastleSize && _y < OutControllSize )
	{
		return OutSkirtOutControll_LeftBottom;
	}else if (_x >= (CitySize - OutCastleSize) && _x < (CitySize - OutControllSize) && _y < OutControllSize)
	{
		return OutSkirtOutControll_LeftTop;
	}else if (_x >= OutControllSize && _x < OutCastleSize && _y >= (CitySize - OutControllSize))
	{
		return OutSkirtOutControll_RightBottom;
	}else if (_x >= (CitySize - OutCastleSize) && _x < (CitySize - OutControllSize) && _y >= (CitySize - OutControllSize))
	{
		return OutSkirtOutControll_RightTop;
	}else if (_x >= CitySize - OutControllSize && _y >= OutControllSize && _y < OutCastleSize)
	{
		return OutSkirtOutControll_TopLeft;
	}else if(_x >= CitySize - OutControllSize && _y >= (CitySize - OutCastleSize) && _y < (CitySize - OutControllSize))
	{
		return OutSkirtOutControll_TopRight;
	}else if (_x < OutControllSize && _y >= OutControllSize && _y < OutCastleSize)
	{
		return OutSkirtOutControll_BottomLeft;
	}else if (_x < OutControllSize && _y >= (CitySize - OutCastleSize) && _y < (CitySize - OutControllSize))
	{
		return OutSkirtOutControll_BottomRight;
	}else if (_x >= OutCastleSize && _x < OutCenterSize && _y < OutControllSize)
	{
		return FarmOutControll_LeftBottom;
	}else if (_x >= (CitySize - OutCenterSize) && _x <(CitySize - OutCastleSize) && _y < OutControllSize)
	{
		return FarmOutControll_LeftTop;
	}else if (_x >= OutCastleSize && _x < OutCenterSize && _y >= (CitySize - OutControllSize))
	{
		return FarmOutControll_RightBottom;
	}else if (_x >= (CitySize - OutCenterSize) && _x < (CitySize - OutCastleSize) && _y >= (CitySize - OutControllSize))
	{
		return FarmOutControll_RightTop;
	}else if (_x >= (CitySize - OutControllSize) && _y >= OutCastleSize && _y < OutCenterSize)
	{
		return FarmOutControll_TopLeft;
	}else if (_x >= (CitySize - OutControllSize) && _y >= (CitySize - OutCenterSize) && _y < (CitySize - OutCastleSize))
	{
		return FarmOutControll_TopRight;
	}else if (_x < OutControllSize && _y >= OutCastleSize && _y < OutCenterSize)
	{
		return FarmOutControll_BottomLeft;
	}else if (_x < OutControllSize && _y >= (CitySize - OutCenterSize) && _y < (CitySize - OutCastleSize))
	{
		return FarmOutControll_BottomRight;
	}
	// Controll
	else if (_x >= OutControllSize && _x < OutCastleSize && _y >= OutControllSize && _y < OutCastleSize)
	{
		return CornerControll_LeftBottom;
	}else if (_x >= (CitySize - OutCastleSize) && _x < (CitySize - OutControllSize) && _y >= OutControllSize && _y < OutCastleSize)
	{
		return CornerControll_LeftTop;
	}else if (_x >= OutControllSize && _x < OutCastleSize && _y >= (CitySize - OutCastleSize) && _y < (CitySize - OutControllSize))
	{
		return CornerControll_RightBottom;
	}else if (_x >= (CitySize - OutCastleSize) && _x < (CitySize - OutControllSize) && _y >= (CitySize - OutCastleSize) && _y < (CitySize - OutControllSize))
	{
		return CornerControll_RightTop;
	}else if (_x >= OutCenterSize && _x < (CitySize - OutCenterSize) && _y >= OutControllSize && _y < OutCastleSize)
	{
		return CenterControll_Left;
	}else if (_x >= OutCenterSize && _x < (CitySize - OutCenterSize) && _y >= (CitySize - OutCastleSize) && _y < (CitySize - OutControllSize))
	{
		return CenterControll_Right;
	}else if (_x >= (CitySize - OutCastleSize) && _x < (CitySize - OutControllSize) && _y >= OutCenterSize && _y < (CitySize - OutCenterSize))
	{
		return CenterControll_Top;
	}else if (_x >= OutControllSize && _x < OutCastleSize && _y >= OutCenterSize && _y < (CitySize - OutCenterSize))
	{
		return CenterControll_Bottom;
	}else if (_x >= OutCastleSize && _x < OutCenterSize && _y >= OutControllSize && _y < OutCastleSize)
	{
		return FarmControll_LeftBottom;
	}else if (_x >= (CitySize - OutCenterSize) && _x < (CitySize - OutCastleSize) && _y >= OutControllSize && _y < OutCastleSize)
	{
		return FarmControll_LeftTop;
	}else if (_x >= OutCastleSize && _x < OutCenterSize && _y >= (CitySize - OutCastleSize) && _y < (CitySize - OutControllSize))
	{
		return FarmControll_RightBottom;
	}else if (_x >= (CitySize - OutCenterSize) && _x < (CitySize - OutCastleSize) && _y >= (CitySize - OutCastleSize) && _y < (CitySize - OutControllSize))
	{
		return FarmControll_RightTop;
	}else if (_x >= (CitySize - OutCastleSize) && _x < (CitySize - OutControllSize) && _y >= OutCastleSize && _y < OutCenterSize)
	{
		return FarmControll_TopLeft;
	}else if (_x >= (CitySize - OutCastleSize) && _x < (CitySize - OutControllSize) && _y >= (CitySize - OutCenterSize) && _y <(CitySize - OutControllSize))
	{
		return FarmControll_TopRight;
	}else if (_x >= OutControllSize && _x < OutCastleSize && _y >= OutCastleSize && _y < OutCenterSize)
	{
		return FarmControll_BottomLeft;
	}else if (_x >= OutControllSize && _x < OutCastleSize && _y >= OutCenterSize && _y < (CitySize - OutCastleSize))
	{
		return FarmControll_BottomRight;
	}
	//  In Castle
	else if (_x >= OutCastleSize && _x < OutCenterSize && _y >= OutCastleSize && _y < OutCenterSize)
	{
		return CornerCastle_LeftBottom;
	}else if (_x >= (CitySize - OutCenterSize) && _x < (CitySize - OutCastleSize) && _y >= OutCastleSize && _y < OutCenterSize)
	{
		return CornerCastle_LeftTop;
	}else if (_x >= OutCastleSize && _x < OutCenterSize && _y >= (CitySize - OutCenterSize) && _y < (CitySize - OutCastleSize))
	{
		return CornerCastle_RightBottom;
	}else if (_x >= (CitySize - OutCenterSize) && _x < (CitySize - OutCastleSize) && _y >= (CitySize - OutCenterSize) && _y < (CitySize - OutCastleSize))
	{
		return CornerCastle_RightTop;
	}else if (_x >= OutCenterSize && _x < (CitySize - OutCenterSize) && _y >= OutCastleSize && _y < OutCenterSize)
	{
		return CenterCastle_Left;
	}else if (_x >= OutCenterSize && _x < (CitySize - OutCenterSize) && _y >= (CitySize - OutCenterSize) && _y < (CitySize - OutCastleSize))
	{
		return CenterCastle_Right;
	}else if (_x >= (CitySize - OutCenterSize) && _x < (CitySize - OutCastleSize) && _y >= OutCenterSize && _y < (CitySize - OutCenterSize))
	{
		return CenterCastle_Top;
	}else if (_x >= OutCastleSize && _x <  OutCenterSize && _y >= OutCenterSize && _y < (CitySize - OutCenterSize))
	{
		return CenterCastle_Bottom;
	}
	return CityCenter;
}
FBuildingIndex ACityActor::GetCenterIndex()
{
	return FBuildingIndex(CitySize / 2, CitySize / 2);
}
FBuildingIndex ACityActor::GetXYLeftBottomIndex()
{
	return FBuildingIndex(0, 0);
}
FBuildingIndex ACityActor::GetXYLeftTopIndex()
{
	return FBuildingIndex(CitySize - 1, 0);
}
FBuildingIndex ACityActor::GetXYRightBottomIndex()
{
	return FBuildingIndex(0, CitySize -1);
}
FBuildingIndex ACityActor::GetXYRightTopIndex()
{
	return FBuildingIndex(CitySize - 1, CitySize - 1);
}