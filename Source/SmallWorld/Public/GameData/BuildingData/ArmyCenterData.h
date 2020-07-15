#pragma once
#include "BaseBuildingData.h"
#include "BaseSoldierData.h"

struct SoldierTrainState
{
	int32			RemainLoopTimes;
	float			CurrentTrainProgress;
	bool			OneLoopIsFinish;
	SoldierTrainState()
		: RemainLoopTimes(0)
		, CurrentTrainProgress(0.f)
		, OneLoopIsFinish(false)
	{

	}
};
struct SoldierStorageState
{
	SoldierEnum	SoldierType;
	int32			HaveNum;
	int32			OutingNum;
	int32			TrainNum;
	
	SoldierStorageState()
		:SoldierType(Soldier_None)
		, HaveNum(0)
		, OutingNum(0)
		, TrainNum(0)
	{

	}
};

class ArmyCenterData : public BaseBuildingData
{
protected:
    
public:

	ArmyCenterData();
    ~ArmyCenterData();
    
    virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer) override;
    virtual void Deserialization(TSharedPtr<FJsonObject>  JsonObject) override;

	virtual bool SpawnBuildingActor(UWorld * world, const FVector & Location, const FRotator & Rotation) override;

	void	TrainSoldier(SoldierEnum InSoldierType,int32 InNum);
    
	void	OnTrainArcherCallback(const float & InProgress, const bool & InIsFinish, const int & LoopTimes);
	void	OnTrainFootmanCallback(const float & InProgress, const bool & InIsFinish, const int & LoopTimes);
	
protected:
	void	OnTrainCallback(SoldierStorageState & StorageState, SoldierTrainState & TrainState, const float & InProgress, const bool & InIsFinish, const int & LoopTimes);
	
	TMap<SoldierEnum, SoldierStorageState>	SoldierStorageMap;
	TMap<SoldierEnum, SoldierTrainState>	SoldierTrainMap;


};
