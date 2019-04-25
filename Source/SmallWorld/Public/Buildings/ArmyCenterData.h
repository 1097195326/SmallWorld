#pragma once
#include "BaseBuildingData.h"


class ArmyCenterData : public BaseBuildingData
{
protected:
    
public:
	ArmyCenterData();
    ~ArmyCenterData();
    
    
    virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer) override;
    virtual void Deserialization(TSharedPtr<FJsonObject>  JsonObject) override;

    
    
    
};
