#pragma once
#include "BaseBuildingData.h"


class CityWallData : public BaseBuildingData
{
protected:
    
public:
	CityWallData();
    ~CityWallData();
    
    
    virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer) override;
    virtual void Deserialization(TSharedPtr<FJsonObject>  JsonObject) override;
    
    
    
    
};
