#pragma once
#include "GameDataClass.h"

class GAMEFRAME_API RuntimeDataClass : public GameDataClass
{
protected:
	

public:
	

	virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer) override;
	virtual void Deserialization(TSharedPtr<FJsonObject>  JsonObject) override;

};