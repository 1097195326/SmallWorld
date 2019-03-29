#pragma once


#include "GObject.h"
#include "Json.h"
#include "XmlParser.h"

class GCORE_API GData : public GObject
{

public :
	virtual void InitWithXML(const FXmlFile * _file);

	
	virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer);
	virtual void Deserialization(TSharedPtr<FJsonObject> JsonObject);

};
