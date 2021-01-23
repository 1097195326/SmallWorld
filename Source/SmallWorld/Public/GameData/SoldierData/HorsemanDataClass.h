#pragma once
#include "BaseSoldierDataClass.h"



class HorsemanDataClass : public BaseSoldierDataClass
{
public:
	HorsemanDataClass();
	virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer) override;
	virtual void Deserialization(TSharedPtr<FJsonObject>  JsonObject) override;

};