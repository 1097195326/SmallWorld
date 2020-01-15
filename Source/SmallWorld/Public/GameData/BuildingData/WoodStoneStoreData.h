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
    
    
	virtual FString GetName() override { return TEXT("WoodStoneStore"); }


	void	ChangeWoodStoneNum(int32 plusWood = 0, int32 plusStone = 0);
	void	GetWoodStoneNum(int32 & OutWoodNum, int32 & OutStoneNum);

protected:

	int32 WoodNum;
	int32 StoneNum;
    
};
