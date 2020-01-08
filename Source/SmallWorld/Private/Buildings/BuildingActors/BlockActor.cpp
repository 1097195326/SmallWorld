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
	
}
FString ABlockActor::GetMeshPath()
{
	FString tileStr = GrassTile;
	
	return tileStr;
}
int ABlockActor::GetFillNum()
{
    return mFillBuildingActors.Num();
}
FVector ABlockActor::GetFillLocation()
{
	int fillNum = mFillBuildingActors.Num();
	FVector temLoc = GetActorLocation();
	switch (fillNum)
	{
	case 0:
	{
		temLoc += FVector(-QuarterTitleSize, -QuarterTitleSize, 0);
		break;
	}
	case 1:
	{
		temLoc += FVector(QuarterTitleSize, -QuarterTitleSize, 0);
		break;
	}
	case 2:
	{
		temLoc += FVector(QuarterTitleSize, QuarterTitleSize, 0);
		break;
	}
	case 3:
	{
		temLoc += FVector(-QuarterTitleSize, QuarterTitleSize, 0);
		break;
	}
	}
	return temLoc;
}
void ABlockActor::FillBuilding(ABaseBuildingActor * _building)
{
    if(mFillBuildingActors.Num() == 0 || mFillBuildingActors.Num() < 4)
    {
        _building->SetOnBlockActor(this);
        mFillBuildingActors.Add(_building);
    }
}
void ABlockActor::RemoveBuilding(ABaseBuildingActor * _building)
{
    mFillBuildingActors.Remove(_building);
    if (mFillBuildingActors.Num() == 0)
    {
    }
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
