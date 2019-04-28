#pragma once
#include "BaseBuildingData.h"

class BlockData : public BaseBuildingData
{
public:
	BuildingType  mFillType;

public:
	BlockData();

	virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer) override;
	virtual void Deserialization(TSharedPtr<FJsonObject>  JsonObject) override;



};