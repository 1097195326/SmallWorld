#pragma once

#include "DataC.h"


class UserData : public DataC
{
public:
	UserData();

	virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer) override;
	virtual void Deserialization(TSharedPtr<FJsonObject>  JsonObject) override;

	const FGuid &	GetHordeId() { return HordeId; }
	void			SetHordeId(const FGuid& hordeId) { HordeId = hordeId; }

	void  SetHordeData(class HordeData * hordeData);
	HordeData * GetHordeData();
private:
	class HordeData * mHordeData;

	FGuid  HordeId;

};


