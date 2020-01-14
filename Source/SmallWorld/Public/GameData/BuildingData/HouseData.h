#pragma once
#include "BaseBuildingData.h"


class HouseData : public BaseBuildingData
{
protected:
    
public:
	HouseData();
    ~HouseData();
    
    
    virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer) override;
    virtual void Deserialization(TSharedPtr<FJsonObject>  JsonObject) override;
    
	virtual FString GetName() override { return TEXT("House"); }

    
    
};
