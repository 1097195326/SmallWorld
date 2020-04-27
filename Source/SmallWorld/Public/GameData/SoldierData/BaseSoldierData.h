#pragma once
#include "DataR.h"

enum SoldierType
{
	S_Archer = 1,
	S_Footman,
	S_Griffin,
	S_Horseman,
	S_Knight,
	S_Mage,
	S_SiegeEngine,
	S_Peasant,
};

class BaseSoldierData : public DataR
{
public:

	virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer) override;
	virtual void Deserialization(TSharedPtr<FJsonObject>  JsonObject) override;

};
