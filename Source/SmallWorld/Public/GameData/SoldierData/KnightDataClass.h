#pragma once
#include "BaseSoldierDataClass.h"



class KnightDataClass : public BaseSoldierDataClass
{
public:
	KnightDataClass();
	virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer) override;
	virtual void Deserialization(TSharedPtr<FJsonObject>  JsonObject) override;

};