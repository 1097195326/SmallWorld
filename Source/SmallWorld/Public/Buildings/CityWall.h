#pragma once
#include "BaseBuilding.h"


class CityWall : public BaseBuilding
{
protected:
    
public:
    CityWall();
    ~CityWall();
    
    
    virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer) override;
    virtual void Deserialization(TSharedPtr<FJsonObject>  JsonObject) override;
    
    
    
    
};
