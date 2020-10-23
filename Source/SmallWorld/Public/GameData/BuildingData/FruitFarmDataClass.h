#pragma once
#include "BaseBuildingDataClass.h"


class FruitFarmDataClass : public BaseBuildingDataClass
{
protected:

public:
	FruitFarmDataClass();
	~FruitFarmDataClass();


	virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer) override;
	virtual void Deserialization(TSharedPtr<FJsonObject>  JsonObject) override;

	virtual ABaseBuildingActor * SpawnBuildingActor(UWorld * world, const FTransform & SpawnTF, const int32 && InIndex = 0) override;


	bool IsFull();
public:
	int32  FruitNum;

};
