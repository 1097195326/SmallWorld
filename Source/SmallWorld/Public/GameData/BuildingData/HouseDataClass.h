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
    
	virtual ABaseBuildingActor * SpawnBuildingActor(UWorld * world, const FTransform & SpawnTF, const int32 && InIndex = 0) override;

	void	ChangePeopleNum(int32 plusNum);
	inline int32	GetPeopleNum() { return PeopleNum; }
protected:
	int32	PeopleNum;
    
};
