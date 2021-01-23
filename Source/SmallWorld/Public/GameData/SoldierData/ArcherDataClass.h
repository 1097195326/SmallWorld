#pragma once
#include "BaseSoldierDataClass.h"



class ArcherDataClass : public BaseSoldierDataClass
{
public:
	ArcherDataClass();

	virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer) override;
	virtual void Deserialization(TSharedPtr<FJsonObject>  JsonObject) override;

};