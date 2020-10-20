#pragma once

#include "ClientDataClass.h"
#include "HordeDataClass.h"

class UserDataClass : public ClientDataClass
{
public:
	friend class GameWorldDataClass;

	UserDataClass();

	virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer) override;
	virtual void Deserialization(TSharedPtr<FJsonObject>  JsonObject) override;

	const FGuid &	GetHordeId() { return HordeId; }
	HordeDataClass * GetHordeData() { return HordeData; }
	void SetHordeData(HordeDataClass * InHordaData);

	void SetCurrentRace(RaceEnum InRace) { CurrentRace = InRace; }
	RaceEnum GetCurrentRace() { return CurrentRace; }
	
private:
	HordeDataClass * HordeData;
	FGuid  HordeId;

	RaceEnum	CurrentRace;

	
};


