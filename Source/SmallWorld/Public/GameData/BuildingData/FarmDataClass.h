#pragma once
#include "BaseBuildingDataClass.h"


class FarmDataClass : public BaseBuildingDataClass
{
protected:
    
public:
	FarmDataClass();
    ~FarmDataClass();
    
    
    virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer) override;
    virtual void Deserialization(TSharedPtr<FJsonObject>  JsonObject) override;
    
	virtual bool SpawnBuildingActor(UWorld * world, const FVector & Location, const FRotator & Rotation) override;

	bool	IsFull();

public:
	int32 CropNum;
    
};
