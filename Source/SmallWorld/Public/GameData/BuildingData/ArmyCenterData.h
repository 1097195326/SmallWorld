#pragma once
#include "BaseBuildingData.h"
#include "BaseSoldierData.h"

class ArmyCenterData : public BaseBuildingData
{
protected:
    
public:
	ArmyCenterData();
    ~ArmyCenterData();
    
    virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer) override;
    virtual void Deserialization(TSharedPtr<FJsonObject>  JsonObject) override;

	virtual bool SpawnBuildingActor(UWorld * world, const FVector & Location, const FRotator & Rotation) override;

	void	TrainSoldier(ESoldierType InSoldierType,int32 InNum);
    
	void	OnTrainArcherCallback(float InProgress, bool InIsFinish, int LoopTimes);
	void	OnTrainFootmanCallback(float InProgress, bool InIsFinish, int LoopTimes);
	

};
