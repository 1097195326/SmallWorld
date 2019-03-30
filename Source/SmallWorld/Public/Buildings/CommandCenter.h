#pragma once
#include "BaseBuilding.h"


class CommandCenter : public BaseBuilding
{
protected:
    
public:
    CommandCenter();
    ~CommandCenter();
    
    
    virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer) override;
    virtual void Deserialization(TSharedPtr<FJsonObject>  JsonObject) override;
    
    
    
    
};
