#pragma once
#include "BaseBuildingDataClass.h"


class TowerDataClass : public BaseBuildingDataClass
{
protected:
    
public:
	TowerDataClass();
    ~TowerDataClass();
    
    
    virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer) override;
    virtual void Deserialization(TSharedPtr<FJsonObject>  JsonObject) override;
    
	virtual ABaseBuildingActor * SpawnBuildingActor(UWorld * world, const FTransform & SpawnTF, const int32 && InIndex = 0) override;


    
};
