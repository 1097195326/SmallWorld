#pragma once


#include "BaseObject.h"
#include "Json.h"
#include "XmlParser.h"


class GAMEFRAME_API GData : public BaseObject
{

public :
	virtual void InitWithXML(const FXmlFile * _file);

	
	virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer);
	virtual void Deserialization(TSharedPtr<FJsonObject> JsonObject);

};
