////#include "GCore.h"
#include "ClientDataClass.h"



void ClientDataClass::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	Writer->WriteObjectStart("ClientDataClass");
	GameDataClass::Serialization(Writer);

	Writer->WriteObjectEnd();//ClientDataClass
}
void ClientDataClass::Deserialization(TSharedPtr<FJsonObject>  JsonObject)
{
	GameDataClass::Deserialization(JsonObject->GetObjectField("GameDataClass"));


}