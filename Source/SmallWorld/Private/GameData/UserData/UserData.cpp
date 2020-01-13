#include "UserData.h"
#include "HordeData.h"


UserData::UserData()
{
	HordeId.Invalidate();
	mHordeData = nullptr;

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
void UserData::SetHordeData(HordeData * hordeData)
{
	mHordeData = hordeData;
}
HordeData * UserData::GetHordeData()
{
	return mHordeData;
}