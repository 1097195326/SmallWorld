#pragma once
#include "BaseBuildingDataClass.h"
#include "BaseSoldierDataClass.h"

class CommandCenterDataClass : public BaseBuildingDataClass
{
protected:
    
public:
	CommandCenterDataClass();
    ~CommandCenterDataClass();
    
    
    virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer) override;
    virtual void Deserialization(TSharedPtr<FJsonObject>  JsonObject) override;
    
	virtual ABaseBuildingActor * SpawnBuildingActor(UWorld * world, const FTransform & SpawnTF, const int32 && InIndex = 0) override;


protected:

	TMap<FGuid, BaseSoldierDataClass*>		SoldiersMap;

    
};
