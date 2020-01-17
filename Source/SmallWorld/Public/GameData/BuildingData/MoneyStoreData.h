#pragma once
#include "BaseBuildingData.h"


class MoneyStoreData : public BaseBuildingData
{
protected:
    
public:
	MoneyStoreData();
    ~MoneyStoreData();
    
    
    virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer) override;
    virtual void Deserialization(TSharedPtr<FJsonObject>  JsonObject) override;
    
    
	virtual FString GetName() override { return TEXT("MoneyStore"); }

	void  ChangeGoldNum(const int32 & plusNum);
	inline int32 GetGoldNum() { return GoldNum; }
protected:
	int32 GoldNum;
    
};
