#include "UserData.h"

void UserData::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	Writer->WriteObjectStart("UserData");
		Writer->WriteValue("HordeId", HordeId);

	Writer->WriteObjectEnd();// UserData
}

void UserData::Deserialization(TSharedPtr<FJsonObject> JsonObject)
{
	JsonObject->TryGetNumberField("HordeId",HordeId);

}
