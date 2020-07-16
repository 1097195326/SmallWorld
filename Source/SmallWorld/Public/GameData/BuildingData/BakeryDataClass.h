#pragma once
#include "BaseBuildingDataClass.h"


class BakeryDataClass : public BaseBuildingDataClass
{
protected:
    
public:
	BakeryDataClass();
    ~BakeryDataClass();
    
    
    virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer) override;
    virtual void Deserialization(TSharedPtr<FJsonObject>  JsonObject) override;
    
	virtual bool SpawnBuildingActor(UWorld * world, const FVector & Location, const FRotator & Rotation) override;


    
};
