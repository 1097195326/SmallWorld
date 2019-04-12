#pragma once
#include "BaseBuildingData.h"

class BlockData : public BaseBuildingData
{
protected:

public:
	virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer) override;
	virtual void Deserialization(TSharedPtr<FJsonObject>  JsonObject) override;



};