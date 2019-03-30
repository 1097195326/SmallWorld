#pragma once
#include "CommandCenter.h"


CommandCenter::CommandCenter()
{
    mType = e_CommandCenter;
    
}
CommandCenter::~CommandCenter()
{
    
}
void CommandCenter::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
    
    
}
void CommandCenter::Deserialization(TSharedPtr<FJsonObject>  JsonObject)
{
    
    
}

