#pragma once


#include "BaseObjectClass.h"
#include "Json.h"
#include "XmlParser.h"


class GAMEFRAME_API GameDataClass : public BaseObjectClass
{
public :
	
	GameDataClass();
	~GameDataClass();


	virtual void	InitWithXML(const FXmlFile * _file);

	inline FGuid	GetParentId() { return ParentId; }
	inline void		SetParentId(FGuid InId) { ParentId = InId; }

	virtual void	Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer);
	virtual void	Deserialization(TSharedPtr<FJsonObject> JsonObject);

	bool operator==(const GameDataClass & data) { return ObjectId == data.ObjectId; }
	bool operator!=(const GameDataClass & data) { return ObjectId != data.ObjectId; }
	bool operator==(const GameDataClass * data) { return ObjectId == data->ObjectId; }
	bool operator!=(const GameDataClass * data) { return ObjectId != data->ObjectId; }

protected:
	
	FGuid ParentId;

};
