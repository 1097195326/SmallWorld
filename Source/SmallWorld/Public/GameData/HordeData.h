#pragma once

#include "BaseBuildingData.h"

class HordeData : public DataR
{
protected:
    
public:
    virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer) override;
    virtual void Deserialization(TSharedPtr<FJsonObject>  JsonObject) override;

    
	TArray<BaseBuildingData*>		BuildingDatas;

private:
	int32 HordeId;
    
};

