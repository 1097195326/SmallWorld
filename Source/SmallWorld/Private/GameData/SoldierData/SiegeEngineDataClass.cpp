#include "SiegeEngineDataClass.h"

G_REGISTER_CLASS(SiegeEngineDataClass)


SiegeEngineDataClass::SiegeEngineDataClass()
{
	SoldierType = Soldier_SiegeEngine;
	MoveType = Move_Walk;

}
void SiegeEngineDataClass::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	Writer->WriteObjectStart("SiegeEngineDataClass");
	BaseSoldierDataClass::Serialization(Writer);

	Writer->WriteObjectEnd();// SiegeEngineDataClass


}
void SiegeEngineDataClass::Deserialization(TSharedPtr<FJsonObject> JsonObject)
{
	BaseSoldierDataClass::Deserialization(JsonObject->GetObjectField("BaseSoldierDataClass"));

}