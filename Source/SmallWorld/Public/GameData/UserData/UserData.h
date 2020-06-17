#pragma once

#include "DataC.h"
#include "BuildingData/HordeData.h"

class UserData : public DataC
{
public:
	friend class GameWorldData;

	UserData();

	virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer) override;
	virtual void Deserialization(TSharedPtr<FJsonObject>  JsonObject) override;

	const FGuid &	GetHordeId() { return hordeId; }
	 HordeData * GetHordeData() { return hordeData; }
private:
	HordeData * hordeData;
	FGuid  hordeId;

};


