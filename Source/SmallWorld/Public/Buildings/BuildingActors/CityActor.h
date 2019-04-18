#pragma once

#include "BaseBuildingActor.h"
#include "BlockActor.h"
#include "CityData.h"
#include "CityActor.generated.h"

UCLASS()
class ACityActor : public ABaseBuildingActor
{
	GENERATED_BODY()

private:
	vector<vector<ABlockActor*>> BlockMap;
	CityData * mData;

	UPROPERTY(VisibleDefaultsOnly)
		UBoxComponent * CollisionBox;

public:
	ACityActor();

	virtual void On_Init() override;
	virtual void On_Delete() override;

	void InitData(CityData * _data);

	virtual FBuildingIndex GetCenterIndex() override;
	virtual FBuildingIndex GetXYLeftBottomIndex() override;
	virtual FBuildingIndex GetXYLeftTopIndex() override;
	virtual FBuildingIndex GetXYRightBottomIndex() override;
	virtual FBuildingIndex GetXYRightTopIndex() override;
};