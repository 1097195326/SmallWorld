//#include "GCore.h"
#include "RuntimeDataClass.h"



void RuntimeDataClass::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	Writer->WriteObjectStart("RuntimeDataClass");
	GameDataClass::Serialization(Writer);

	Writer->WriteObjectEnd();//RuntimeDataClass
}
void RuntimeDataClass::Deserialization(TSharedPtr<FJsonObject>  JsonObject)
{
	GameDataClass::Deserialization(JsonObject->GetObjectField("GameDataClass"));


}
