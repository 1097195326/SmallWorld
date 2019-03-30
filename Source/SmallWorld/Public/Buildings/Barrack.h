#pragma once
#include "BaseBuilding.h"


class Barrack : public BaseBuilding
{
protected:
    
public:
    Barrack();
    ~Barrack();
    
    
    virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer) override;
    virtual void Deserialization(TSharedPtr<FJsonObject>  JsonObject) override;

    
    
    
};
