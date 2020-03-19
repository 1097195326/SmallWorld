#pragma once
#include "BaseBuildingData.h"


class FruitFarmData : public BaseBuildingData
{
protected:

public:
	FruitFarmData();
	~FruitFarmData();


	virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer) override;
	virtual void Deserialization(TSharedPtr<FJsonObject>  JsonObject) override;



	bool IsFull();
public:
	int32  FruitNum;

};
