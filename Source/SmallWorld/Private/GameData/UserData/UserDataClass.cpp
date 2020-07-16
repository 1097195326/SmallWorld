#include "UserDataClass.h"


UserDataClass::UserDataClass()
{
	HordeId.Invalidate();
	HordeData = nullptr;

}
void UserDataClass::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	Writer->WriteObjectStart("UserDataClass");
	ClientDataClass::Serialization(Writer);

		Writer->WriteValue("HordeId", HordeId.ToString());

	Writer->WriteObjectEnd();// UserDataClass
}

void UserDataClass::Deserialization(TSharedPtr<FJsonObject> JsonObject)
{

	ClientDataClass::Deserialization(JsonObject->GetObjectField("ClientDataClass"));
	FGuid::Parse(JsonObject->GetStringField("HordeId"), HordeId);


}
