#include "BlockData.h"

G_REGISTER_CLASS(BlockData)


BlockData::BlockData()
{
	BuildingType = B_CityBlock;

}
void BlockData::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{


}
void BlockData::Deserialization(TSharedPtr<FJsonObject>  JsonObject)
{


}
