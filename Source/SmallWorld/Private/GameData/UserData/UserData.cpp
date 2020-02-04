#include "UserData.h"
#include "HordeData.h"


UserData::UserData()
{
	hordeId.Invalidate();
	hordeData = nullptr;

}
void UserData::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	Writer->WriteObjectStart("UserData");
	DataC::Serialization(Writer);

		Writer->WriteValue("HordeId", hordeId.ToString());

	Writer->WriteObjectEnd();// UserData
}

void UserData::Deserialization(TSharedPtr<FJsonObject> JsonObject)
{

	DataC::Deserialization(JsonObject->GetObjectField("DataC"));
	FGuid::Parse(JsonObject->GetStringField("HordeId"), hordeId);


}
