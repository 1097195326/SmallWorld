#pragma once
#include "BaseBuildingData.h"


class WoodStoreData : public BaseBuildingData
{
protected:
    
public:
	WoodStoreData();
    ~WoodStoreData();
    
    
    virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer) override;
    virtual void Deserialization(TSharedPtr<FJsonObject>  JsonObject) override;
    
    
    
    
};
