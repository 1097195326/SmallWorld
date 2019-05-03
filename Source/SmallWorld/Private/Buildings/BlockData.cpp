#include "BlockData.h"



BlockData::BlockData()
{
    mType = B_CityBlock;
    
}
void BlockData::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{


}
void BlockData::Deserialization(TSharedPtr<FJsonObject>  JsonObject)
{


}
