//#include "GCore.h"
#include "GData.h"

GData::GData()
{
	GDataType = None;
	ParentId.Invalidate();
}
GData::~GData()
{
	GDataType = None;
}
void GData::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	Writer->WriteObjectStart("GData");
	Writer->WriteValue("m_ID", m_ID.ToString());
	Writer->WriteValue("ParentId", ParentId.ToString());
	Writer->WriteObjectEnd();//GData

}
void GData::Deserialization(TSharedPtr<FJsonObject> JsonObject)
{
	FString temId,temParentId;

	JsonObject->TryGetStringField("m_ID", temId);
	JsonObject->TryGetStringField("ParentId", temParentId);

	if (!temId.IsEmpty()){FGuid::Parse(temId, m_ID);}
	if (!temParentId.IsEmpty()) {FGuid::Parse(temParentId, ParentId);}

}
void GData::InitWithXML(const FXmlFile * _file)
{
	
}
