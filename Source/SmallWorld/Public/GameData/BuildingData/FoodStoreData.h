#pragma once
#include "BaseBuildingData.h"


class FoodStoreData : public BaseBuildingData
{
protected:
    
public:
	FoodStoreData();
    ~FoodStoreData();
    
    
    virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer) override;
    virtual void Deserialization(TSharedPtr<FJsonObject>  JsonObject) override;
    
    
	virtual FString GetName() override { return TEXT("FoodStore"); }

    
};
