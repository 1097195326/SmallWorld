#pragma once
#include "BaseBuildingDataClass.h"


class HouseDataClass : public BaseBuildingDataClass
{
protected:
    
public:
	HouseDataClass();
    ~HouseDataClass();
    
    
    virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer) override;
    virtual void Deserialization(TSharedPtr<FJsonObject>  JsonObject) override;
    
	virtual bool SpawnBuildingActor(UWorld * world, const FVector & Location, const FRotator & Rotation) override;

	void	ChangePeopleNum(int32 plusNum);
	inline int32	GetPeopleNum() { return PeopleNum; }
protected:
	int32	PeopleNum;
    
};
