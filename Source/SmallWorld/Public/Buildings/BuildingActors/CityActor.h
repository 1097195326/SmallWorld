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
	int		CitySize;
public:
	ACityActor();

	void InitData(CityData * _data);


};