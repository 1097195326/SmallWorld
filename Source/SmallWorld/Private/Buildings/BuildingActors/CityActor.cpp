#include "CityActor.h"


ACityActor::ACityActor()
{
	mCityIsFull = false;
	mCenterCityIsFull = false;

	RootComponent = CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetHiddenInGame(false);
	CollisionBox->ShapeColor = FColor(0,255,0,255);

	BaseMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CityMeshComponent"));
	BaseMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	BaseMeshComponent->SetRelativeScale3D(FVector(0.1f));

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
				BlockActor->InitData(new BlockData());
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
	
	// Insert CanBuild titles
	ControllBuildTiles.insert(ControllBuildTiles.end(), CornerCastleLeftBottom.begin(), CornerCastleLeftBottom.end());
	ControllBuildTiles.insert(ControllBuildTiles.end(), CornerCastleLeftTop.begin(), CornerCastleLeftTop.end());
	ControllBuildTiles.insert(ControllBuildTiles.end(), CornerCastleRightTop.begin(), CornerCastleRightTop.end());
	ControllBuildTiles.insert(ControllBuildTiles.end(), CornerCastleRightBottom.begin(), CornerCastleRightBottom.end());

	ControllBuildTiles.insert(ControllBuildTiles.end(), FarmControllLeftBottom.begin(), FarmControllLeftBottom.end());
	ControllBuildTiles.insert(ControllBuildTiles.end(), FarmControllLeftTop.begin(), FarmControllLeftTop.end());
	ControllBuildTiles.insert(ControllBuildTiles.end(), FarmControllTopLeft.begin(), FarmControllTopLeft.end());
	ControllBuildTiles.insert(ControllBuildTiles.end(), FarmControllTopRight.begin(), FarmControllTopRight.end());
	ControllBuildTiles.insert(ControllBuildTiles.end(), FarmControllRightTop.begin(), FarmControllRightTop.end());
	ControllBuildTiles.insert(ControllBuildTiles.end(), FarmControllRightBottom.begin(), FarmControllRightBottom.end());
	ControllBuildTiles.insert(ControllBuildTiles.end(), FarmControllBottomLeft.begin(), FarmControllBottomLeft.end());
	ControllBuildTiles.insert(ControllBuildTiles.end(), FarmControllBottomRight.begin(), FarmControllBottomRight.end());

	ControllBuildTiles.insert(ControllBuildTiles.end(), FarmOutControllLeftBottom.begin(), FarmOutControllLeftBottom.end());
	ControllBuildTiles.insert(ControllBuildTiles.end(), FarmOutControllLeftTop.begin(), FarmOutControllLeftTop.end());
	ControllBuildTiles.insert(ControllBuildTiles.end(), FarmOutControllTopLeft.begin(), FarmOutControllTopLeft.end());
	ControllBuildTiles.insert(ControllBuildTiles.end(), FarmOutControllTopRight.begin(), FarmOutControllTopRight.end());
	ControllBuildTiles.insert(ControllBuildTiles.end(), FarmOutControllRightTop.begin(), FarmOutControllRightTop.end());
	ControllBuildTiles.insert(ControllBuildTiles.end(), FarmOutControllRightBottom.begin(), FarmOutControllRightBottom.end());
	ControllBuildTiles.insert(ControllBuildTiles.end(), FarmOutControllBottomLeft.begin(), FarmOutControllBottomLeft.end());
	ControllBuildTiles.insert(ControllBuildTiles.end(), FarmOutControllBottomRight.begin(), FarmOutControllBottomRight.end());

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
int ACityActor::GetFarmNum()
{
	return FarmList.size();
}
int ACityActor::GetHouseNum()
{
	return HouseList.size();
}
int ACityActor::GetMillNum()
{
	return MillList.size();
}
int ACityActor::GetBakeryNum()
{
	return BakeryList.size();
}
int ACityActor::GetMoneyStoreNum()
{
	return MoneyStoreList.size();
}
int ACityActor::GetFoodStoreNum()
{
	return FoodStoreList.size();
}
int ACityActor::GetStoneStoreNum()
{
	return StoneStoreList.size();
}
int ACityActor::GetWoodStoreNum()
{
	return WoodStoreList.size();
}
int ACityActor::GetCommandCenterLevel()
{
	return CommandCenterList.size();
	/*if (!CommandCenterList.empty())
	{
		return (*CommandCenterList.begin())->GetLevel();
	}
	return 0;*/
}
int ACityActor::GetArmyCenterLevel()
{
	return ArmyCenterList.size();
}
int ACityActor::GetWallLevel()
{
	if (WallList.empty())
	{
		return 0;
	}
	return 1;
}
int ACityActor::GetBakeryLevel()
{
	return BakeryList.size();
}
int ACityActor::GetMillLevel()
{
	return MillList.size();
}
int ACityActor::GetMoneyStoreLevel()
{
	return MoneyStoreList.size();
}
int ACityActor::GetFoodStoreLevel()
{
	return FoodStoreList.size();
}
int ACityActor::GetStoneStoreLevel()
{
	return StoneStoreList.size();
}
int ACityActor::GetWoodStoreLevel()
{
	return WoodStoreList.size();
}
bool ACityActor::CityIsFull()
{
	return mCityIsFull;
}
bool ACityActor::CenterCityIsFull()
{
	return mCenterCityIsFull;
}
bool ACityActor::CheckCanBuildCommandCenter(ABlockActor *& OutBlockActor, FString & OutMsg)
{
	if (CommandCenterList.empty())
	{
		OutBlockActor = CenterOfCenterCity;
		return true;
	}
	return false;
}
bool ACityActor::CheckCanBuildArmyCenter(ABlockActor *& OutBlockActor, FString & OutMsg)
{
	if (ArmyCenterList.empty())
	{
		for (auto  blockActor : CenterCity)
		{
			if (blockActor->GetTileType() == T_GrassTile)
			{
				OutBlockActor = blockActor;
				return true;
			}
			else
			{
				mCenterCityIsFull = true;
			}
		}
	}
	return false;
}
bool ACityActor::CheckCanBuildBakery(ABlockActor *& OutBlockActor, FString & OutMsg)
{
	if (mCityIsFull)
	{
		return false;
	}
	for (auto blockActor : ControllBuildTiles)
	{
		if ((blockActor->GetTileType() == T_FullDirtTile && blockActor->GetFillNum() < 4)
            || blockActor->GetTileType() == T_GrassTile)
		{
			OutBlockActor = blockActor;
			return true;
		}
	}
	mCityIsFull = true;

	return false;
}
bool ACityActor::CheckCanBuildFarm(ABlockActor *& OutBlockActor, FString & OutMsg)
{
	if (mCityIsFull)
	{
		return false;
	}
	for (auto blockActor : ControllBuildTiles)
	{
        if ((blockActor->GetTileType() == T_FullDirtTile && blockActor->GetFillNum() < 4)
            || blockActor->GetTileType() == T_GrassTile)
		{
			OutBlockActor = blockActor;
			return true;
		}
	}
	mCityIsFull = true;
	return false;
}
bool ACityActor::CheckCanBuildHouse(ABlockActor *& OutBlockActor, FString & OutMsg)
{
	if (mCityIsFull)
	{
		return false;
	}
	for (auto blockActor : ControllBuildTiles)
	{
        if ((blockActor->GetTileType() == T_FullDirtTile && blockActor->GetFillNum() < 4)
            || blockActor->GetTileType() == T_GrassTile)
		{
			OutBlockActor = blockActor;
			return true;
		}
	}
	mCityIsFull = true;
	return false;
}
bool ACityActor::CheckCanBuildMill(ABlockActor *& OutBlockActor, FString & OutMsg)
{
	if (mCityIsFull)
	{
		return false;
	}
	for (auto blockActor : ControllBuildTiles)
	{
        if ((blockActor->GetTileType() == T_FullDirtTile && blockActor->GetFillNum() < 4)
            || blockActor->GetTileType() == T_GrassTile)
		{
			OutBlockActor = blockActor;
			return true;
		}
	}
	mCityIsFull = true;
	return false;
}
bool ACityActor::CheckCanBuildMoneyStore(ABlockActor *& OutBlockActor, FString & OutMsg)
{
	if (mCenterCityIsFull)
	{
		return false;
	}
	for (auto blockActor : CenterCity)
	{
        if ((blockActor->GetTileType() == T_FullDirtTile && blockActor->GetFillNum() < 4)
            || blockActor->GetTileType() == T_GrassTile)
		{
			OutBlockActor = blockActor;
			return true;
		}
	}
	mCenterCityIsFull = true;
	return false;
}
bool ACityActor::CheckCanBuildFoodStore(ABlockActor *& OutBlockActor, FString & OutMsg)
{
	if (mCenterCityIsFull)
	{
		return false;
	}
	for (auto blockActor : CenterCity)
	{
		if (blockActor->GetTileType() == T_GrassTile)
		{
			OutBlockActor = blockActor;
			return true;
		}
	}
	mCenterCityIsFull = true;
	return false;
}
bool ACityActor::CheckCanBuildStoneStore(ABlockActor *& OutBlockActor, FString & OutMsg)
{
	if (mCenterCityIsFull)
	{
		return false;
	}
	for (auto blockActor : CenterCity)
	{
        if ((blockActor->GetTileType() == T_FullDirtTile && blockActor->GetFillNum() < 4)
            || blockActor->GetTileType() == T_GrassTile)
		{
			OutBlockActor = blockActor;
			return true;
		}
	}
	mCenterCityIsFull = true;
	return false;
}
bool ACityActor::CheckCanBuildWoodStore(ABlockActor *& OutBlockActor, FString & OutMsg)
{
	if (mCenterCityIsFull)
	{
		return false;
	}
	for (auto blockActor : CenterCity)
	{
        if ((blockActor->GetTileType() == T_FullDirtTile && blockActor->GetFillNum() < 4)
            || blockActor->GetTileType() == T_GrassTile)
		{
			OutBlockActor = blockActor;
			return true;
		}
	}
	mCenterCityIsFull = true;
	return false;
}
bool ACityActor::CheckCanBuildWall(ABlockActor *& OutBlockActor, FString & OutMsg)
{
	if (WallList.empty())
	{
		return true;
	}
	return false;
}
bool ACityActor::BuildCommandCenter()
{
	ABlockActor * blockActor = nullptr;
	FString ResSmg;
	bool Result = CheckCanBuildCommandCenter(blockActor, ResSmg);
	if (Result)
	{
		FTransform trans(blockActor->GetActorLocation());
		ACommandCenterActor * BuildActor = Cast<ACommandCenterActor>(UGameplayStatics::BeginDeferredActorSpawnFromClass(SWI, ACommandCenterActor::StaticClass(), trans));
		if (BuildActor)
		{
			BuildActor->InitData(new CommandCenterData());
            blockActor->FillBuilding(BuildActor);
			
			CommandCenterList.push_back(BuildActor);
			UGameplayStatics::FinishSpawningActor(BuildActor, trans);
		}
	}
	return Result;
}
bool ACityActor::BuildArmyCenter()
{
	ABlockActor * blockActor = nullptr;
	FString ResSmg;
	bool Result = CheckCanBuildArmyCenter(blockActor, ResSmg);
	if (Result)
	{
		FTransform trans(blockActor->GetActorLocation());
		AArmyCenterActor * BuildActor = Cast<AArmyCenterActor>(UGameplayStatics::BeginDeferredActorSpawnFromClass(SWI, AArmyCenterActor::StaticClass(), trans));
		if (BuildActor)
		{
            BuildActor->InitData(new ArmyCenterData());
			blockActor->FillBuilding(BuildActor);

			ArmyCenterList.push_back(BuildActor);
			UGameplayStatics::FinishSpawningActor(BuildActor, trans);
		}
	}
	return Result;
}
bool ACityActor::BuildBakery()
{
	ABlockActor * blockActor = nullptr;
	FString ResSmg;
	bool Result = CheckCanBuildBakery(blockActor, ResSmg);
	if (Result)
	{
		FTransform trans(blockActor->GetActorLocation());
		ABakeryActor * BuildActor = Cast<ABakeryActor>(UGameplayStatics::BeginDeferredActorSpawnFromClass(SWI, ABakeryActor::StaticClass(), trans));
		if (BuildActor)
		{
            BuildActor->InitData(new BlockData());
			blockActor->FillBuilding(BuildActor);

			BakeryList.push_back(BuildActor);
			UGameplayStatics::FinishSpawningActor(BuildActor, trans);
		}
	}
	return Result;
}
bool ACityActor::BuildFarm()
{
	ABlockActor * blockActor = nullptr;
	FString ResSmg;
	bool Result = CheckCanBuildFarm(blockActor, ResSmg);
	if (Result)
	{
		FTransform trans(blockActor->GetActorLocation());
		AFarmActor * BuildActor = Cast<AFarmActor>(UGameplayStatics::BeginDeferredActorSpawnFromClass(SWI, AFarmActor::StaticClass(), trans));
		if (BuildActor)
		{
            BuildActor->InitData(new FarmData());
			blockActor->FillBuilding(BuildActor);

			FarmList.push_back(BuildActor);
			UGameplayStatics::FinishSpawningActor(BuildActor, trans);
		}
	}
	return Result;
}
bool ACityActor::BuildHouse()
{
	ABlockActor * blockActor = nullptr;
	FString ResSmg;
	bool Result = CheckCanBuildHouse(blockActor, ResSmg);
	if (Result)
	{
		FTransform trans(blockActor->GetActorLocation());
		AHouseActor * BuildActor = Cast<AHouseActor>(UGameplayStatics::BeginDeferredActorSpawnFromClass(SWI, AHouseActor::StaticClass(), trans));
		if (BuildActor)
		{
            BuildActor->InitData(new HouseData());
			blockActor->FillBuilding(BuildActor);

			HouseList.push_back(BuildActor);
			UGameplayStatics::FinishSpawningActor(BuildActor, trans);
		}
	}
	return Result;
}
bool ACityActor::BuildMill()
{
	ABlockActor * blockActor = nullptr;
	FString ResSmg;
	bool Result = CheckCanBuildMill(blockActor, ResSmg);
	if (Result)
	{
		FTransform trans(blockActor->GetActorLocation());
		AMillActor * BuildActor = Cast<AMillActor>(UGameplayStatics::BeginDeferredActorSpawnFromClass(SWI, AMillActor::StaticClass(), trans));
		if (BuildActor)
		{
            BuildActor->InitData(new MillData());
			blockActor->FillBuilding(BuildActor);

			
			MillList.push_back(BuildActor);
			UGameplayStatics::FinishSpawningActor(BuildActor, trans);
		}
	}
	return Result;
}
bool ACityActor::BuildMoneyStore()
{
	ABlockActor * blockActor = nullptr;
	FString ResSmg;
	bool Result = CheckCanBuildMoneyStore(blockActor, ResSmg);
	if (Result)
	{
		FTransform trans(blockActor->GetActorLocation());
		AMoneyStoreActor * BuildActor = Cast<AMoneyStoreActor>(UGameplayStatics::BeginDeferredActorSpawnFromClass(SWI, AMoneyStoreActor::StaticClass(), trans));
		if (BuildActor)
		{
            BuildActor->InitData(new MoneyStoreData());
			blockActor->FillBuilding(BuildActor);

			
			MoneyStoreList.push_back(BuildActor);
			UGameplayStatics::FinishSpawningActor(BuildActor, trans);
		}
	}
	return Result;
}
bool ACityActor::BuildFoodStore()
{
	ABlockActor * blockActor = nullptr;
	FString ResSmg;
	bool Result = CheckCanBuildFoodStore(blockActor, ResSmg);
	if (Result)
	{
		FTransform trans(blockActor->GetActorLocation());
		AFoodStoreActor * BuildActor = Cast<AFoodStoreActor>(UGameplayStatics::BeginDeferredActorSpawnFromClass(SWI, AFoodStoreActor::StaticClass(), trans));
		if (BuildActor)
		{
            BuildActor->InitData(new FoodStoreData());
			blockActor->FillBuilding(BuildActor);

			
			FoodStoreList.push_back(BuildActor);
			UGameplayStatics::FinishSpawningActor(BuildActor, trans);
		}
	}
	return Result;
}
bool ACityActor::BuildStoneStore()
{
	ABlockActor * blockActor = nullptr;
	FString ResSmg;
	bool Result = CheckCanBuildStoneStore(blockActor, ResSmg);
	if (Result)
	{
		FTransform trans(blockActor->GetActorLocation());
		AStoneStoreActor * BuildActor = Cast<AStoneStoreActor>(UGameplayStatics::BeginDeferredActorSpawnFromClass(SWI, AStoneStoreActor::StaticClass(), trans));
		if (BuildActor)
		{
            BuildActor->InitData(new StoneStoreData());
			blockActor->FillBuilding(BuildActor);

			
			StoneStoreList.push_back(BuildActor);
			UGameplayStatics::FinishSpawningActor(BuildActor, trans);
		}
	}
	return Result;
}
bool ACityActor::BuildWoodStore()
{
	ABlockActor * blockActor = nullptr;
	FString ResSmg;
	bool Result = CheckCanBuildWoodStore(blockActor, ResSmg);
	if (Result)
	{
		FTransform trans(blockActor->GetActorLocation());
		AWoodStoreActor * BuildActor = Cast<AWoodStoreActor>(UGameplayStatics::BeginDeferredActorSpawnFromClass(SWI, AWoodStoreActor::StaticClass(), trans));
		if (BuildActor)
		{
            BuildActor->InitData(new WoodStoreData());
			blockActor->FillBuilding(BuildActor);

			
			WoodStoreList.push_back(BuildActor);
			UGameplayStatics::FinishSpawningActor(BuildActor, trans);
		}
	}
	return Result;
}
bool ACityActor::BuildWall()
{
	ABlockActor * blockActor = nullptr;
	FString ResSmg;
	bool Result = CheckCanBuildWall(blockActor, ResSmg);
	if (Result)
	{
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
				DirV = FVector(1, 0, 0);
				Dir = Dir_CastleEdge_Left;
			}
			else if (i == 1)
			{
				Origin = FVector(CastleWallXOffSet + CastleWallLength, CastleWallYOffSet, 0);
				DirV = FVector(0, 1, 0);
				Dir = Dir_CastleEdge_Top;
			}
			else if (i == 2)
			{
				Origin = FVector(CastleWallXOffSet + CastleWallLength, CastleWallYOffSet + CastleWallLength, 0);
				DirV = FVector(-1, 0, 0);
				Dir = Dir_CastleEdge_Right;
			}
			else if (i == 3)
			{
				Origin = FVector(CastleWallXOffSet, CastleWallYOffSet + CastleWallLength, 0);
				DirV = FVector(0, -1, 0);
				Dir = Dir_CastleEdge_Bottom;
			}
			for (int j = 0; j < (int)(CastleWallLength / WallSize); j++)
			{
				FTransform trans(Origin + DirV * WallSize * j);
				ABaseBuildingActor * BuildingActor = nullptr;
				if (j == 0)
				{
					BuildingActor = Cast<ATowerActor>(UGameplayStatics::BeginDeferredActorSpawnFromClass(SWI, ATowerActor::StaticClass(), trans));
					BuildingActor->InitData(new TowerData());
					TowerList.push_back((ATowerActor*)BuildingActor);
				}
				else if (j == (int)CastleWallLength / WallSize / 2)
				{
					BuildingActor = Cast<AGateActor>(UGameplayStatics::BeginDeferredActorSpawnFromClass(SWI, AGateActor::StaticClass(), trans));
					BuildingActor->InitData(new GateData());
					GateList.push_back((AGateActor*)BuildingActor);
				}
				else
				{
					BuildingActor = Cast<AWallActor>(UGameplayStatics::BeginDeferredActorSpawnFromClass(SWI, AWallActor::StaticClass(), trans));
					BuildingActor->InitData(new WallData());
					WallList.push_back((AWallActor*)BuildingActor);
				}
				if (BuildingActor)
				{
					BuildingActor->SetDirection(Dir);
					UGameplayStatics::FinishSpawningActor(BuildingActor, trans);
				}
			}
		}
	}
	return Result;
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
	}else if (_x == CitySize/2 && _y == CitySize/2)
	{
		CenterOfCenterCity = _blockActor;
		_blockActor->SetOrientation(CenterOfCenter_City);
		return ;
	}
	CenterCity.push_back(_blockActor);
	_blockActor->SetOrientation(Center_City);
	return ;
}
