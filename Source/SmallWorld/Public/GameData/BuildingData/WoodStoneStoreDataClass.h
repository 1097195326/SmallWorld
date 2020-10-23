#pragma once
#include "BaseBuildingDataClass.h"


class WoodStoneStoreDataClass : public BaseBuildingDataClass
{
protected:
    
public:
	WoodStoneStoreDataClass();
    ~WoodStoneStoreDataClass();
    
    
    virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer) override;
    virtual void Deserialization(TSharedPtr<FJsonObject>  JsonObject) override;
    
	virtual ABaseBuildingActor * SpawnBuildingActor(UWorld * world, const FTransform & SpawnTF, const int32 && InIndex = 0) override;

	void	ChangeWoodNum(const int32 & plusWood);
	void	ChangeStoneNum(const int32 & plusStone);
	inline int32	GetStoneNum() { return StoneNum; }
	inline int32	GetWoodNum(){return WoodNum;}

protected:

	int32 WoodNum;
	int32 StoneNum;
    
};
