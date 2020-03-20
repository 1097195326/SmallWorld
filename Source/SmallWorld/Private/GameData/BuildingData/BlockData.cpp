#include "BlockData.h"
#include "BlockActor.h"


G_REGISTER_CLASS(BlockData)


BlockData::BlockData()
{
	

}
void BlockData::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{


}
void BlockData::Deserialization(TSharedPtr<FJsonObject>  JsonObject)
{


}
bool BlockData::SpawnBuildingActor(UWorld * world, const FVector & Location, const FRotator & Rotation)
{

	return false;
}