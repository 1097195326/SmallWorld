#pragma once

#include "GameDataClass.h"


class GAMEFRAME_API TemplateDataClass : public GameDataClass
{
protected:
	
public:
	

	virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer);
	virtual void Deserialization(TSharedPtr<FJsonObject> JsonObject);


};