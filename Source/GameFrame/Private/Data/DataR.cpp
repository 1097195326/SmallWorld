//#include "GCore.h"
#include "DataR.h"



void DataR::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	Writer->WriteObjectStart("DataR");
	GData::Serialization(Writer);

	Writer->WriteObjectEnd();//DataR
}
void DataR::Deserialization(TSharedPtr<FJsonObject>  JsonObject)
{
	GData::Deserialization(JsonObject->GetObjectField("GData"));


}
