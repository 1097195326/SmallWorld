#pragma once
#include "BaseBuildingData.h"


class FoodStoreData : public BaseBuildingData
{
protected:
    
public:
	FoodStoreData();
    ~FoodStoreData();
    
    
    virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer) override;
    virtual void Deserialization(TSharedPtr<FJsonObject>  JsonObject) override;
    
    
	virtual FString GetName() override { return TEXT("FoodStore"); }

	void	ChangeFoodNum(int32 plusCrop = 0, int32 plusBreak = 0, int32 plusFruit = 0);
	void	GetFoodNum(int32 & OutCropNum, int32 & OutBreadNum, int32 & OutFruitNuM);

protected:
	int32 CropNum;
	int32 BreadNum;
	int32 FruitNum;

};
