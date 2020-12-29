#include "ArcherDataClass.h"

G_REGISTER_CLASS(ArcherDataClass)


void ArcherDataClass::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	Writer->WriteObjectStart("ArcherDataClass");
		BaseSoldierDataClass::Serialization(Writer);

	Writer->WriteObjectEnd();// ArcherDataClass

}
void ArcherDataClass::Deserialization(TSharedPtr<FJsonObject> JsonObject)
{
	BaseSoldierDataClass::Deserialization(JsonObject->GetObjectField("BaseSoldierDataClass"));
	

}