#pragma once
#include "BaseBuildingData.h"


class WallData : public BaseBuildingData
{
protected:
    
public:
	WallData();
    ~WallData();
    
    
    virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer) override;
    virtual void Deserialization(TSharedPtr<FJsonObject>  JsonObject) override;
    
	virtual FString GetName() override { return TEXT("Wall"); }

    
    
};
