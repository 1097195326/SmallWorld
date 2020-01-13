#pragma once

#include "GData.h"


class GAMEFRAME_API DataT : public GData
{
protected:
	
public:
	

	virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer);
	virtual void Deserialization(TSharedPtr<FJsonObject> JsonObject);


};