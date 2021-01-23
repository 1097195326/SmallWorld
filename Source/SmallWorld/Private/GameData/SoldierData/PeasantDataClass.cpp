#include "PeasantDataClass.h"

G_REGISTER_CLASS(PeasantDataClass)


PeasantDataClass::PeasantDataClass()
{
	SoldierType = Soldier_Peasant;
	MoveType = Move_Walk;

}
void PeasantDataClass::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	Writer->WriteObjectStart("PeasantDataClass");
	BaseSoldierDataClass::Serialization(Writer);

	Writer->WriteObjectEnd();// PeasantDataClass


}
void PeasantDataClass::Deserialization(TSharedPtr<FJsonObject> JsonObject)
{
	BaseSoldierDataClass::Deserialization(JsonObject->GetObjectField("BaseSoldierDataClass"));

}