#pragma once
#include "BaseBuildingData.h"


class GameWorldData : public BaseBuildingData
{
protected:
    
public:
	GameWorldData();
    ~GameWorldData();
    
    
    virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer) override;
    virtual void Deserialization(TSharedPtr<FJsonObject>  JsonObject) override;
    
    
    
    
};
