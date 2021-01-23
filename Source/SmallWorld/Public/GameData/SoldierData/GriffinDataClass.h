#pragma once
#include "BaseSoldierDataClass.h"



class GriffinDataClass : public BaseSoldierDataClass
{
public:
	GriffinDataClass();
	virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer) override;
	virtual void Deserialization(TSharedPtr<FJsonObject>  JsonObject) override;

};