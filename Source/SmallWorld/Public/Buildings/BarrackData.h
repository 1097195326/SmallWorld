#pragma once
#include "BaseBuildingData.h"


class BarrackData : public BaseBuildingData
{
protected:
    
public:
	BarrackData();
    ~BarrackData();
    
    
    virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer) override;
    virtual void Deserialization(TSharedPtr<FJsonObject>  JsonObject) override;

    
    
    
};
