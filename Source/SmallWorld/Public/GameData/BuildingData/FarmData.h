#pragma once
#include "BaseBuildingData.h"


class FarmData : public BaseBuildingData
{
protected:
    
public:
	FarmData();
    ~FarmData();
    
    
    virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer) override;
    virtual void Deserialization(TSharedPtr<FJsonObject>  JsonObject) override;
    
	virtual FString GetName() override { return TEXT("Farm"); }

    
    
};
