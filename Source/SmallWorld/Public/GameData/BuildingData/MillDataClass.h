#pragma once
#include "BaseBuildingDataClass.h"


class MillDataClass : public BaseBuildingDataClass
{
protected:
    
public:
	MillDataClass();
    ~MillDataClass();
    
    
    virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer) override;
    virtual void Deserialization(TSharedPtr<FJsonObject>  JsonObject) override;
    
	virtual bool SpawnBuildingActor(UWorld * world, const FTransform & SpawnTF, const int32 && InIndex = 0) override;

    
    
};
