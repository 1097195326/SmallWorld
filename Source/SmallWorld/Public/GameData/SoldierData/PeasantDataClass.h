#pragma once
#include "BaseSoldierDataClass.h"



class PeasantDataClass : public BaseSoldierDataClass
{
public:

	virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer) override;
	virtual void Deserialization(TSharedPtr<FJsonObject>  JsonObject) override;

};