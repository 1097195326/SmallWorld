
#include "GameDataClass.h"

GameDataClass::GameDataClass()
{
	
	ParentId.Invalidate();
}
GameDataClass::~GameDataClass()
{
	
}
void GameDataClass::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	Writer->WriteObjectStart("GameDataClass");
	Writer->WriteValue("ObjectId", ObjectId.ToString());
	Writer->WriteValue("ParentId", ParentId.ToString());
	Writer->WriteObjectEnd();//GameDataClass

}
void GameDataClass::Deserialization(TSharedPtr<FJsonObject> JsonObject)
{
	FString temId,temParentId;

	JsonObject->TryGetStringField("ObjectId", temId);
	JsonObject->TryGetStringField("ParentId", temParentId);

	if (!temId.IsEmpty()){FGuid::Parse(temId, ObjectId);}
	if (!temParentId.IsEmpty()) {FGuid::Parse(temParentId, ParentId);}

}
void GameDataClass::InitWithXML(const FXmlFile * _file)
{
	
}
