#include "HorsemanDataClass.h"

G_REGISTER_CLASS(HorsemanDataClass)


HorsemanDataClass::HorsemanDataClass()
{
	SoldierType = Soldier_Horseman;
	MoveType = Move_Walk;

}
void HorsemanDataClass::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	Writer->WriteObjectStart("HorsemanDataClass");
	BaseSoldierDataClass::Serialization(Writer);

	Writer->WriteObjectEnd();// HorsemanDataClass


}
void HorsemanDataClass::Deserialization(TSharedPtr<FJsonObject> JsonObject)
{
	BaseSoldierDataClass::Deserialization(JsonObject->GetObjectField("BaseSoldierDataClass"));

}