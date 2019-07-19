//#include "GCore.h"
#include "GData.h"

void GData::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	

}
void GData::Deserialization(TSharedPtr<FJsonObject> JsonObject)
{
	int ss = JsonObject->GetNumberField("");

}
void GData::InitWithXML(const FXmlFile * _file)
{
	
}
