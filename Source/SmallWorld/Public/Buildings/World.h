#pragma once

#include "BaseBuilding.h"


class World : public BaseBuilding
{
    
public:
    virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer) override;
    virtual void Deserialization(TSharedPtr<FJsonObject>  JsonObject) override;

};
