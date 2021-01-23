#include "MageDataClass.h"

G_REGISTER_CLASS(MageDataClass)


MageDataClass::MageDataClass()
{
	SoldierType = Soldier_Mage;
	MoveType = Move_Walk;

}
void MageDataClass::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	Writer->WriteObjectStart("MageDataClass");
	BaseSoldierDataClass::Serialization(Writer);

	Writer->WriteObjectEnd();// MageDataClass


}
void MageDataClass::Deserialization(TSharedPtr<FJsonObject> JsonObject)
{
	BaseSoldierDataClass::Deserialization(JsonObject->GetObjectField("BaseSoldierDataClass"));

}