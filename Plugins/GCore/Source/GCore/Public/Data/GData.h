#pragma once


#include "GObject.h"
#include "Json.h"
#include "XmlParser.h"

class GCORE_API GData : public GObject
{

public :
	virtual void InitWithJson(const TSharedPtr<FJsonObject> &obj);
	virtual void InitWithXML(const FXmlFile * _file);
};
