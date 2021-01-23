#include "KnightDataClass.h"

G_REGISTER_CLASS(KnightDataClass)


KnightDataClass::KnightDataClass()
{
	SoldierType = Soldier_Knight;
	MoveType = Move_Walk;

}
void KnightDataClass::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	Writer->WriteObjectStart("KnightDataClass");
	BaseSoldierDataClass::Serialization(Writer);

	Writer->WriteObjectEnd();// KnightDataClass


}
void KnightDataClass::Deserialization(TSharedPtr<FJsonObject> JsonObject)
{
	BaseSoldierDataClass::Deserialization(JsonObject->GetObjectField("BaseSoldierDataClass"));

}