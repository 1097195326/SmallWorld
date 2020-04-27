#pragma once
#include "BaseSoldierData.h"



class ArcherData : public BaseSoldierData
{
public:

	virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer) override;
	virtual void Deserialization(TSharedPtr<FJsonObject>  JsonObject) override;

};