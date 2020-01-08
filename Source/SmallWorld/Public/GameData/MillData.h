#pragma once
#include "BaseBuildingData.h"


class MillData : public BaseBuildingData
{
protected:
    
public:
	MillData();
    ~MillData();
    
    
    virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer) override;
    virtual void Deserialization(TSharedPtr<FJsonObject>  JsonObject) override;
    
    
    
    
};
