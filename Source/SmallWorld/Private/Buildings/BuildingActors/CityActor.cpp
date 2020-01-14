#include "CityActor.h"


ACityActor::ACityActor()
{
	mCityIsFull = false;
	mCenterCityIsFull = false;

	//mGeneralGoal = new GeneralGoal();
	//mGeneralGoal->InitWithCityActor(this);

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

	// Bild City Bound Moutain
	if (!IsInWorld())
	{
		const FString Mountain1 = "/Game/CastlePack/Meshes/SM_01_Moutain";
		const FString Mountain2 = "/Game/CastlePack/Meshes/SM_02_Moutain";

		UStaticMesh * mesh = LoadObject<UStaticMesh>(this, *Mountain1);
		BaseMeshComponent->SetStaticMesh(mesh);
	}

	//mGeneralGoal->Enter();
}
void ACityActor::On_GameUpdate()
{
	
	//if (mGeneralGoal)
	//{
	//	//mGeneralGoal->Process();
	//}
	for (auto groupManager : mGroupManagers)
	{
		groupManager->On_GameUpdate();
	}

}
void ACityActor::On_Delete()
{
	//mGeneralGoal->End();

	/*delete mGeneralGoal;
	mGeneralGoal = nullptr;*/
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
			if (blockActor->GetFillNum() < 1)
			{
				OutBlockActor = blockActor;
				return true;
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
	
	mCityIsFull = true;

	return false;
}
bool ACityActor::CheckCanBuildFarm(ABlockActor *& OutBlockActor, FString & OutMsg)
{
	if (mCityIsFull)
	{
		return false;
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
	
	mCityIsFull = true;
	return false;
}
bool ACityActor::CheckCanBuildMill(ABlockActor *& OutBlockActor, FString & OutMsg)
{
	if (mCityIsFull)
	{
		return false;
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
	
	mCenterCityIsFull = true;
	return false;
}
bool ACityActor::CheckCanBuildFoodStore(ABlockActor *& OutBlockActor, FString & OutMsg)
{
	if (mCenterCityIsFull)
	{
		return false;
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
	
	mCenterCityIsFull = true;
	return false;
}
bool ACityActor::CheckCanBuildWoodStore(ABlockActor *& OutBlockActor, FString & OutMsg)
{
	if (mCenterCityIsFull)
	{
		return false;
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
		FTransform trans(blockActor->GetFillLocation());
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
		FTransform trans(blockActor->GetFillLocation());
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
		FTransform trans(blockActor->GetFillLocation());
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
		FTransform trans(blockActor->GetFillLocation());
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
		FTransform trans(blockActor->GetFillLocation());
		AWoodStoneStoreActor * BuildActor = Cast<AWoodStoneStoreActor>(UGameplayStatics::BeginDeferredActorSpawnFromClass(SWI, AWoodStoneStoreActor::StaticClass(), trans));
		if (BuildActor)
		{
            BuildActor->InitData(new WoodStoneStoreData());
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
		FTransform trans(blockActor->GetFillLocation());
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
	
	return Result;
}
void ACityActor::CalCulateOrientation(int _x, int _y,ABlockActor * _blockActor)
{
	// OutControll 
	const int OutControllSize = (CitySize - CastleControllSize) * 0.5;
	const int OutCastleSize = (CitySize - CastleSize) * 0.5;
	const int OutCenterSize = (CitySize - CastleCenterSize) * 0.5;

	
	return ;
}
