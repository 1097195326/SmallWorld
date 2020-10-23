#pragma once
#include "BaseBuildingDataClass.h"
#include "BaseSoldierDataClass.h"

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
	SoldierTypeEnum	SoldierType;
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

class ArmyCenterDataClass : public BaseBuildingDataClass
{
protected:
    
public:

	ArmyCenterDataClass();
    ~ArmyCenterDataClass();
    
    virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer) override;
    virtual void Deserialization(TSharedPtr<FJsonObject>  JsonObject) override;

	virtual ABaseBuildingActor * SpawnBuildingActor(UWorld * world, const FTransform & SpawnTF, const int32 && InIndex = 0) override;

	void	TrainSoldier(SoldierTypeEnum InSoldierType,int32 InNum);
    
	void	OnTrainArcherCallback(const float & InProgress, const bool & InIsFinish, const int & LoopTimes);
	void	OnTrainFootmanCallback(const float & InProgress, const bool & InIsFinish, const int & LoopTimes);
	
protected:
	void	OnTrainCallback(SoldierStorageState & StorageState, SoldierTrainState & TrainState, const float & InProgress, const bool & InIsFinish, const int & LoopTimes);
	
	TMap<SoldierTypeEnum, SoldierStorageState>	SoldierStorageMap;
	TMap<SoldierTypeEnum, SoldierTrainState>	SoldierTrainMap;


};
