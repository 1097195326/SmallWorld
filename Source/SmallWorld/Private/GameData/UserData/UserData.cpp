#include "UserData.h"

UserData::UserData()
{
	HordeId = FGuid::NewGuid();

}
void UserData::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	Writer->WriteObjectStart("UserData");
		Writer->WriteValue("HordeId", HordeId.ToString());

	Writer->WriteObjectEnd();// UserData
}

void UserData::Deserialization(TSharedPtr<FJsonObject> JsonObject)
{
	FGuid::Parse(JsonObject->GetStringField("HordeId"),HordeId) ;

}
