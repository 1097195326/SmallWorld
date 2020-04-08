#pragma once


#include "BaseObject.h"
#include "Json.h"
#include "XmlParser.h"


class GAMEFRAME_API GData : public BaseObject
{
public :
	
	GData();
	~GData();


	virtual void	InitWithXML(const FXmlFile * _file);

	inline FGuid	GetParentId() { return ParentId; }
	inline void		SetParentId(FGuid InId) { ParentId = InId; }

	virtual void	Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer);
	virtual void	Deserialization(TSharedPtr<FJsonObject> JsonObject);

	bool operator==(const GData & data) { return m_ID == data.m_ID; }
	bool operator!=(const GData & data) { return m_ID != data.m_ID; }
	bool operator==(const GData * data) { return m_ID == data->m_ID; }
	bool operator!=(const GData * data) { return m_ID != data->m_ID; }

protected:
	
	FGuid ParentId;

};
