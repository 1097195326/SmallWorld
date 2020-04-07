//#include "GCore.h"
#include "GData.h"

GData::GData()
{
	GDataType = None;
}
GData::~GData()
{
	GDataType = None;
}
void GData::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	Writer->WriteObjectStart("GData");
		Writer->WriteValue("m_ID", m_ID.ToString());
	Writer->WriteObjectEnd();//GData

}
void GData::Deserialization(TSharedPtr<FJsonObject> JsonObject)
{
	FString temId;
	JsonObject->TryGetStringField("m_ID", temId);
	if (!temId.IsEmpty())
	{
		FGuid::Parse(temId, m_ID);
	}


}
void GData::InitWithXML(const FXmlFile * _file)
{
	
}
