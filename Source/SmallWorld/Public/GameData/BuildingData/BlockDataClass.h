#pragma once
#include "BaseBuildingDataClass.h"

class BlockDataClass : public BaseBuildingDataClass
{
public:
	

public:
	BlockDataClass();

	virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer) override;
	virtual void Deserialization(TSharedPtr<FJsonObject>  JsonObject) override;

	virtual ABaseBuildingActor * SpawnBuildingActor(UWorld * world, const FTransform & SpawnTF, const int32 & InIndex) override;


};
