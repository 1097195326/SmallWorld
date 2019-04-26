#pragma once
#include "BaseBuildingData.h"


class GateData : public BaseBuildingData
{
protected:
    
public:
	GateData();
    ~GateData();
    
    
    virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer) override;
    virtual void Deserialization(TSharedPtr<FJsonObject>  JsonObject) override;
    
    
    
    
};
