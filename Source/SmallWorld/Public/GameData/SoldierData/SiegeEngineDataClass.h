#pragma once
#include "BaseSoldierDataClass.h"



class SiegeEngineDataClass : public BaseSoldierDataClass
{
public:
	SiegeEngineDataClass();
	virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer) override;
	virtual void Deserialization(TSharedPtr<FJsonObject>  JsonObject) override;

};