#pragma once
#include "BaseBuildingData.h"


class BakeryData : public BaseBuildingData
{
protected:
    
public:
	BakeryData();
    ~BakeryData();
    
    
    virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer) override;
    virtual void Deserialization(TSharedPtr<FJsonObject>  JsonObject) override;
    
    

    
};
