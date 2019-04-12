#pragma once
#include "DataR.h"

enum BuildingType
{
    e_Barrack,
    e_CityWall,
    e_CommandCenter,
    e_House
};


class BaseBuildingData : public DataR
{

protected:
	float	Health;
	int		Level;
    BuildingType mType;

public:
	virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer) override;
	virtual void Deserialization(TSharedPtr<FJsonObject>  JsonObject) override;


};
