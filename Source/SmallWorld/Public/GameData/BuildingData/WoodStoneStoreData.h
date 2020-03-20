#pragma once
#include "BaseBuildingData.h"


class WoodStoneStoreData : public BaseBuildingData
{
protected:
    
public:
	WoodStoneStoreData();
    ~WoodStoneStoreData();
    
    
    virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer) override;
    virtual void Deserialization(TSharedPtr<FJsonObject>  JsonObject) override;
    
	virtual bool SpawnBuildingActor(UWorld * world, const FVector & Location, const FRotator & Rotation) override;

	void	ChangeWoodNum(const int32 & plusWood);
	void	ChangeStoneNum(const int32 & plusStone);
	inline int32	GetStoneNum() { return StoneNum; }
	inline int32	GetWoodNum(){return WoodNum;}

protected:

	int32 WoodNum;
	int32 StoneNum;
    
};
