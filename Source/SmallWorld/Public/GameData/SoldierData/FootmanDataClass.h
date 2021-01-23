#pragma once
#include "BaseSoldierDataClass.h"



class FootmanDataClass : public BaseSoldierDataClass
{
public:
	FootmanDataClass();
	virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer) override;
	virtual void Deserialization(TSharedPtr<FJsonObject>  JsonObject) override;

};