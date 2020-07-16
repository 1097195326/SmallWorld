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

	const FGuid &	GetHordeId() { return hordeId; }
	 HordeDataClass * GetHordeData() { return hordeData; }
private:
	HordeDataClass * hordeData;
	FGuid  hordeId;

};


