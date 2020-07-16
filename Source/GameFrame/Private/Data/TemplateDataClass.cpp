//#include "GCore.h"

#include "TemplateDataClass.h"




void TemplateDataClass::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	Writer->WriteObjectStart("TemplateDataClass");
	GameDataClass::Serialization(Writer);

	Writer->WriteObjectEnd();//TemplateDataClass
}
void TemplateDataClass::Deserialization(TSharedPtr<FJsonObject>  JsonObject)
{
	GameDataClass::Deserialization(JsonObject->GetObjectField("GameDataClass"));


}
