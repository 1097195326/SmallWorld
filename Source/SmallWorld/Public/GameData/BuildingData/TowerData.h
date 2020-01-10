#pragma once
#include "BaseBuildingData.h"


class TowerData : public BaseBuildingData
{
protected:
    
public:
	TowerData();
    ~TowerData();
    
    
    virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer) override;
    virtual void Deserialization(TSharedPtr<FJsonObject>  JsonObject) override;
    
    
    
    
};
