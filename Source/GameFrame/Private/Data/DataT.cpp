//#include "GCore.h"

#include "DataT.h"




void DataT::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	Writer->WriteObjectStart("DataT");
	GData::Serialization(Writer);

	Writer->WriteObjectEnd();//DataT
}
void DataT::Deserialization(TSharedPtr<FJsonObject>  JsonObject)
{
	GData::Deserialization(JsonObject->GetObjectField("GData"));


}
