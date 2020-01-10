#pragma once
#include "BaseBuildingData.h"


class MoneyStoreData : public BaseBuildingData
{
protected:
    
public:
	MoneyStoreData();
    ~MoneyStoreData();
    
    
    virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer) override;
    virtual void Deserialization(TSharedPtr<FJsonObject>  JsonObject) override;
    
    
    
    
};
