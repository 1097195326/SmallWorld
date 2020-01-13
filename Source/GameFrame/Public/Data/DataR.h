#pragma once
#include "GData.h"

class GAMEFRAME_API DataR : public GData
{
protected:
	

public:
	

	virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer) override;
	virtual void Deserialization(TSharedPtr<FJsonObject>  JsonObject) override;

};