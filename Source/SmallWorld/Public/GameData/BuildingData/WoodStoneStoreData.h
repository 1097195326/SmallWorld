#pragma once
#include "BaseBuildingData.h"


class WoodStoneStoreData : public BaseBuildingData
{
protected:
    
public:
	WoodStoneStoreData();
    ~WoodStoneStoreData();
    
    
    virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer) override;
    virtual void Deserialization(TSharedPtr<FJsonObject>  JsonObject) override;
    
    
	virtual FString GetName() override { return TEXT("WoodStoneStore"); }

    
};
