#pragma once

#include "DataC.h"


class UserData : public DataC
{
public:

	virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer) override;
	virtual void Deserialization(TSharedPtr<FJsonObject>  JsonObject) override;

	const int32 &	GetHordeId() { return HordeId; }

private:

	int32  HordeId;

};


