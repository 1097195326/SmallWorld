#pragma once
#include "BaseBuildingDataClass.h"


class MoneyStoreDataClass : public BaseBuildingDataClass
{
protected:
    
public:
	MoneyStoreDataClass();
    ~MoneyStoreDataClass();
    
    
    virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer) override;
    virtual void Deserialization(TSharedPtr<FJsonObject>  JsonObject) override;
    
	virtual ABaseBuildingActor * SpawnBuildingActor(UWorld * world, const FTransform & SpawnTF, const int32 & InIndex) override;


	void  ChangeGoldNum(const int32 & plusNum);
	inline int32 GetGoldNum() { return GoldNum; }
protected:
	int32 GoldNum;
    
};
