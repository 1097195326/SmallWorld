#pragma once
#include "BaseBuilding.h"


class House : public BaseBuilding
{
protected:
    
public:
    House();
    ~House();
    
    
    virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer) override;
    virtual void Deserialization(TSharedPtr<FJsonObject>  JsonObject) override;
    
    
    
    
};
