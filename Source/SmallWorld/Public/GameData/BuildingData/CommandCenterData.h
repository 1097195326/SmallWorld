#pragma once
#include "BaseBuildingData.h"


class CommandCenterData : public BaseBuildingData
{
protected:
    
public:
	CommandCenterData();
    ~CommandCenterData();
    
    
    virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer) override;
    virtual void Deserialization(TSharedPtr<FJsonObject>  JsonObject) override;
    

    
    
};
