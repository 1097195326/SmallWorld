#pragma once
#include "BaseBuildingData.h"


class TreeStoreData : public BaseBuildingData
{
protected:
    
public:
	TreeStoreData();
    ~TreeStoreData();
    
    
    virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer) override;
    virtual void Deserialization(TSharedPtr<FJsonObject>  JsonObject) override;
    
    
    
    
};
