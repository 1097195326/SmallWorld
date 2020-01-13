////#include "GCore.h"
#include "DataC.h"



void DataC::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	Writer->WriteObjectStart("DataC");
	GData::Serialization(Writer);

	Writer->WriteObjectEnd();//DataC
}
void DataC::Deserialization(TSharedPtr<FJsonObject>  JsonObject)
{
	GData::Deserialization(JsonObject->GetObjectField("GData"));


}