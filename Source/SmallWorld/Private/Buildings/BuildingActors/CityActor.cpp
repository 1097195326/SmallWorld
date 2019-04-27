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
void ACityActor::InitData(BaseBuildingData * _data)
{
	mData = _data;
}
void ACityActor::On_Init()
{
	float CityExtent = CitySize * TitleSize * 0.5f;
	CollisionBox->SetBoxExtent(FVector(CityExtent, CityExtent, CityExtent));

	// build City Map
	const float CityXOffSet = mData->mIndex.X * CitySize * TitleSize;
	const float CityYOffSet = mData->mIndex.Y * CitySize * TitleSize;

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
				BlockActor->SetIndex(BuildingIndex(x, y));
				if (IsInWorld())
				{
					CalCulateOrientation(x, y,BlockActor);

				}
				BlockList.push_back(BlockActor);
				UGameplayStatics::FinishSpawningActor(BlockActor, trans);
			}
		}
		BlockMap.push_back(BlockList);
	}
	
	// build castle wall
	const int OutCastleSize = (CitySize - CastleSize) * 0.5;
	const float CastleWallXOffSet = mData->mIndex.X * CitySize * TitleSize + TitleSize * OutCastleSize + TitleSize * 0.5;
	const float CastleWallYOffSet = mData->mIndex.Y * CitySize * TitleSize + TitleSize * OutCastleSize + TitleSize * 0.5;
	const float CastleWallLength = TitleSize * (CastleSize - 1);
	for (int i = 0; i < 4; i++)
	{
		BuildingDirection Dir = Dir_None;
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
void ACityActor::CalCulateOrientation(int _x, int _y,ABlockActor * _blockActor)
{
	// OutControll 
	const int OutControllSize = (CitySize - CastleControllSize) * 0.5;
	const int OutCastleSize = (CitySize - CastleSize) * 0.5;
	const int OutCenterSize = (CitySize - CastleCenterSize) * 0.5;

	if (_x <  OutControllSize && _y < OutControllSize)
	{
		CornerOutControllLeftBottom.push_back(_blockActor);
		_blockActor->SetOrientation(CornerOutControll_LeftBottom);
		return ;
	}else if (_x >= (CitySize - OutControllSize) && _y < OutControllSize)
	{
		CornerOutControllLeftTop.push_back(_blockActor);
		_blockActor->SetOrientation(CornerOutControll_LeftTop);
		return ;
	}else if (_x <  OutControllSize && _y >= (CitySize - OutControllSize))
	{
		CornerOutControllRightBottom.push_back(_blockActor);
		_blockActor->SetOrientation(CornerOutControll_RightBottom);
		return ;
	}else if (_x >= (CitySize - OutControllSize) && _y >= (CitySize - OutControllSize))
	{
		CornerOutControllRightTop.push_back(_blockActor);
		_blockActor->SetOrientation(CornerOutControll_RightTop);
		return ;
	}else if ( _x >= OutCenterSize && _x < (CitySize - OutCenterSize) && _y < OutControllSize)
	{
		CenterOutControllLeft.push_back(_blockActor);
		_blockActor->SetOrientation(CenterOutControll_Left);
		return ;
	}else if (_x >= OutCenterSize && _x < (CitySize - OutCenterSize) && _y >= (CitySize - OutControllSize))
	{
		CenterOutControllRight.push_back(_blockActor);
		_blockActor->SetOrientation(CenterOutControll_Right);
		return ;
	}else if (_y >= OutCenterSize && _y < (CitySize - OutCenterSize) && _x >= (CitySize - OutControllSize))
	{
		CenterOutControllTop.push_back(_blockActor);
		_blockActor->SetOrientation(CenterOutControll_Top);
		return ;
	}else if (_y >= OutCenterSize && _y < (CitySize - OutCenterSize) && _x  < OutControllSize)
	{
		CenterOutControllBottom.push_back(_blockActor);
		_blockActor->SetOrientation(CenterOutControll_Bottom);
		return ;
	}else if (_x >= OutControllSize && _x < OutCastleSize && _y < OutControllSize )
	{
		OutSkirtOutControllLeftBottom.push_back(_blockActor);
		_blockActor->SetOrientation(OutSkirtOutControll_LeftBottom);
		return ;
	}else if (_x >= (CitySize - OutCastleSize) && _x < (CitySize - OutControllSize) && _y < OutControllSize)
	{
		OutSkirtOutControllLeftTop.push_back(_blockActor);
		_blockActor->SetOrientation(OutSkirtOutControll_LeftTop);
		return ;
	}else if (_x >= OutControllSize && _x < OutCastleSize && _y >= (CitySize - OutControllSize))
	{
		OutSkirtOutControllRightBottom.push_back(_blockActor);
		_blockActor->SetOrientation(OutSkirtOutControll_RightBottom);
		return ;
	}else if (_x >= (CitySize - OutCastleSize) && _x < (CitySize - OutControllSize) && _y >= (CitySize - OutControllSize))
	{
		OutSkirtOutControllRightTop.push_back(_blockActor);
		_blockActor->SetOrientation(OutSkirtOutControll_RightTop);
		return ;
	}else if (_x >= CitySize - OutControllSize && _y >= OutControllSize && _y < OutCastleSize)
	{
		OutSkirtOutControllTopLeft.push_back(_blockActor);
		_blockActor->SetOrientation(OutSkirtOutControll_TopLeft);
		return ;
	}else if(_x >= CitySize - OutControllSize && _y >= (CitySize - OutCastleSize) && _y < (CitySize - OutControllSize))
	{
		OutSkirtOutControllTopRight.push_back(_blockActor);
		_blockActor->SetOrientation(OutSkirtOutControll_TopRight);
		return ;
	}else if (_x < OutControllSize && _y >= OutControllSize && _y < OutCastleSize)
	{
		OutSkirtOutControllBottomLeft.push_back(_blockActor);
		_blockActor->SetOrientation(OutSkirtOutControll_BottomLeft);
		return ;
	}else if (_x < OutControllSize && _y >= (CitySize - OutCastleSize) && _y < (CitySize - OutControllSize))
	{
		OutSkirtOutControllBottomRight.push_back(_blockActor);
		_blockActor->SetOrientation(OutSkirtOutControll_BottomRight);
		return ;
	}else if (_x >= OutCastleSize && _x < OutCenterSize && _y < OutControllSize)
	{
		FarmOutControllLeftBottom.push_back(_blockActor);
		_blockActor->SetOrientation(FarmOutControll_LeftBottom);
		return ;
	}else if (_x >= (CitySize - OutCenterSize) && _x <(CitySize - OutCastleSize) && _y < OutControllSize)
	{
		FarmOutControllLeftTop.push_back(_blockActor);
		_blockActor->SetOrientation(FarmOutControll_LeftTop);
		return ;
	}else if (_x >= OutCastleSize && _x < OutCenterSize && _y >= (CitySize - OutControllSize))
	{
		FarmOutControllRightBottom.push_back(_blockActor);
		_blockActor->SetOrientation(FarmOutControll_RightBottom);
		return ;
	}else if (_x >= (CitySize - OutCenterSize) && _x < (CitySize - OutCastleSize) && _y >= (CitySize - OutControllSize))
	{
		FarmOutControllRightBottom.push_back(_blockActor);
		_blockActor->SetOrientation(FarmOutControll_RightTop);
		return ;
	}else if (_x >= (CitySize - OutControllSize) && _y >= OutCastleSize && _y < OutCenterSize)
	{
		FarmOutControllTopLeft.push_back(_blockActor);
		_blockActor->SetOrientation(FarmOutControll_TopLeft);
		return ;
	}else if (_x >= (CitySize - OutControllSize) && _y >= (CitySize - OutCenterSize) && _y < (CitySize - OutCastleSize))
	{
		FarmOutControllTopRight.push_back(_blockActor);
		_blockActor->SetOrientation(FarmOutControll_TopRight);
		return ;
	}else if (_x < OutControllSize && _y >= OutCastleSize && _y < OutCenterSize)
	{
		FarmOutControllBottomLeft.push_back(_blockActor);
		_blockActor->SetOrientation(FarmOutControll_BottomLeft);
		return ;
	}else if (_x < OutControllSize && _y >= (CitySize - OutCenterSize) && _y < (CitySize - OutCastleSize))
	{
		FarmOutControllBottomRight.push_back(_blockActor);
		_blockActor->SetOrientation(FarmOutControll_BottomRight);
		return ;
	}
	// Controll
	else if (_x >= OutControllSize && _x < OutCastleSize && _y >= OutControllSize && _y < OutCastleSize)
	{
		CornerControllLeftBottom.push_back(_blockActor);
		_blockActor->SetOrientation(CornerControll_LeftBottom);
		return ;
	}else if (_x >= (CitySize - OutCastleSize) && _x < (CitySize - OutControllSize) && _y >= OutControllSize && _y < OutCastleSize)
	{
		CornerControllLeftTop.push_back(_blockActor);
		_blockActor->SetOrientation(CornerControll_LeftTop);
		return ;
	}else if (_x >= OutControllSize && _x < OutCastleSize && _y >= (CitySize - OutCastleSize) && _y < (CitySize - OutControllSize))
	{
		CornerControllRightBottom.push_back(_blockActor);
		_blockActor->SetOrientation(CornerControll_RightBottom);
		return ;
	}else if (_x >= (CitySize - OutCastleSize) && _x < (CitySize - OutControllSize) && _y >= (CitySize - OutCastleSize) && _y < (CitySize - OutControllSize))
	{
		CornerControllRightTop.push_back(_blockActor);
		_blockActor->SetOrientation(CornerControll_RightTop);
		return ;
	}else if (_x >= OutCenterSize && _x < (CitySize - OutCenterSize) && _y >= OutControllSize && _y < OutCastleSize)
	{
		CenterControllLeft.push_back(_blockActor);
		_blockActor->SetOrientation(CenterControll_Left);
		return ;
	}else if (_x >= OutCenterSize && _x < (CitySize - OutCenterSize) && _y >= (CitySize - OutCastleSize) && _y < (CitySize - OutControllSize))
	{
		CenterControllRight.push_back(_blockActor);
		_blockActor->SetOrientation(CenterControll_Right);
		return ;
	}else if (_x >= (CitySize - OutCastleSize) && _x < (CitySize - OutControllSize) && _y >= OutCenterSize && _y < (CitySize - OutCenterSize))
	{
		CenterControllTop.push_back(_blockActor);
		_blockActor->SetOrientation(CenterControll_Top);
		return ;
	}else if (_x >= OutControllSize && _x < OutCastleSize && _y >= OutCenterSize && _y < (CitySize - OutCenterSize))
	{
		CenterControllBottom.push_back(_blockActor);
		_blockActor->SetOrientation(CenterControll_Bottom);
		return ;
	}else if (_x >= OutCastleSize && _x < OutCenterSize && _y >= OutControllSize && _y < OutCastleSize)
	{
		FarmControllLeftBottom.push_back(_blockActor);
		_blockActor->SetOrientation(FarmControll_LeftBottom);
		return ;
	}else if (_x >= (CitySize - OutCenterSize) && _x < (CitySize - OutCastleSize) && _y >= OutControllSize && _y < OutCastleSize)
	{
		FarmControllLeftTop.push_back(_blockActor);
		_blockActor->SetOrientation(FarmControll_LeftTop);
		return ;
	}else if (_x >= OutCastleSize && _x < OutCenterSize && _y >= (CitySize - OutCastleSize) && _y < (CitySize - OutControllSize))
	{
		FarmControllRightBottom.push_back(_blockActor);
		_blockActor->SetOrientation(FarmControll_RightBottom);
		return ;
	}else if (_x >= (CitySize - OutCenterSize) && _x < (CitySize - OutCastleSize) && _y >= (CitySize - OutCastleSize) && _y < (CitySize - OutControllSize))
	{
		FarmControllRightTop.push_back(_blockActor);
		_blockActor->SetOrientation(FarmControll_RightTop);
		return ;
	}else if (_x >= (CitySize - OutCastleSize) && _x < (CitySize - OutControllSize) && _y >= OutCastleSize && _y < OutCenterSize)
	{
		FarmControllTopLeft.push_back(_blockActor);
		_blockActor->SetOrientation(FarmControll_TopLeft);
		return ;
	}else if (_x >= (CitySize - OutCastleSize) && _x < (CitySize - OutControllSize) && _y >= (CitySize - OutCenterSize) && _y <(CitySize - OutControllSize))
	{
		FarmControllTopRight.push_back(_blockActor);
		_blockActor->SetOrientation(FarmControll_TopRight);
		return ;
	}else if (_x >= OutControllSize && _x < OutCastleSize && _y >= OutCastleSize && _y < OutCenterSize)
	{
		FarmControllBottomLeft.push_back(_blockActor);
		_blockActor->SetOrientation(FarmControll_BottomLeft);
		return ;
	}else if (_x >= OutControllSize && _x < OutCastleSize && _y >= OutCenterSize && _y < (CitySize - OutCastleSize))
	{
		FarmControllBottomRight.push_back(_blockActor);
		_blockActor->SetOrientation(FarmControll_BottomRight);
		return ;
	}
	//  In Castle
	else if (_x >= OutCastleSize && _x < OutCenterSize && _y >= OutCastleSize && _y < OutCenterSize)
	{
		CornerCastleLeftBottom.push_back(_blockActor);
		_blockActor->SetOrientation(CornerCastle_LeftBottom);
		return ;
	}else if (_x >= (CitySize - OutCenterSize) && _x < (CitySize - OutCastleSize) && _y >= OutCastleSize && _y < OutCenterSize)
	{
		CornerCastleLeftTop.push_back(_blockActor);
		_blockActor->SetOrientation(CornerCastle_LeftTop);
		return ;
	}else if (_x >= OutCastleSize && _x < OutCenterSize && _y >= (CitySize - OutCenterSize) && _y < (CitySize - OutCastleSize))
	{
		CornerCastleRightBottom.push_back(_blockActor);
		_blockActor->SetOrientation(CornerCastle_RightBottom);
		return ;
	}else if (_x >= (CitySize - OutCenterSize) && _x < (CitySize - OutCastleSize) && _y >= (CitySize - OutCenterSize) && _y < (CitySize - OutCastleSize))
	{
		CornerCastleRightTop.push_back(_blockActor);
		_blockActor->SetOrientation(CornerCastle_RightTop);
		return ;
	}else if (_x >= OutCenterSize && _x < (CitySize - OutCenterSize) && _y >= OutCastleSize && _y < OutCenterSize)
	{
		CenterCastleLeft.push_back(_blockActor);
		_blockActor->SetOrientation(CenterCastle_Left);
		return ;
	}else if (_x >= OutCenterSize && _x < (CitySize - OutCenterSize) && _y >= (CitySize - OutCenterSize) && _y < (CitySize - OutCastleSize))
	{
		CenterCastleRight.push_back(_blockActor);
		_blockActor->SetOrientation(CenterCastle_Right);
		return ;
	}else if (_x >= (CitySize - OutCenterSize) && _x < (CitySize - OutCastleSize) && _y >= OutCenterSize && _y < (CitySize - OutCenterSize))
	{
		CenterCastleTop.push_back(_blockActor);
		_blockActor->SetOrientation(CenterCastle_Top);
		return ;
	}else if (_x >= OutCastleSize && _x <  OutCenterSize && _y >= OutCenterSize && _y < (CitySize - OutCenterSize))
	{
		CenterCastleBottom.push_back(_blockActor);
		_blockActor->SetOrientation(CenterCastle_Bottom);
		return ;
	}else if (_x == CitySize/2,_y == CitySize/2)
	{
		CenterOfCenterCity = _blockActor;
		_blockActor->SetOrientation(CenterOfCenter_City);
		return ;
	}
	CenterCity.push_back(_blockActor);
	_blockActor->SetOrientation(Center_City);
	return ;
}
