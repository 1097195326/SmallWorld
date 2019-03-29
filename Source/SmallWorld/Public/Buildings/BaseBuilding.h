#pragma once
#include "DataR.h"

class BaseBuilding : public DataR
{

protected:
	float	Health;
	int		Level;


public:
	virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer) override;
	virtual void Deserialization(TSharedPtr<FJsonObject>  JsonObject) override;


};