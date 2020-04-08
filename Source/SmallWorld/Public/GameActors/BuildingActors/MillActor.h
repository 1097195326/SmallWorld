#pragma once
#include "BaseBuildingActor.h"
#include "MillData.h"

#include "MillActor.generated.h"

UCLASS()
class AMillActor : public ABaseBuildingActor
{
	GENERATED_BODY()

public:
	AMillActor();

	virtual void On_Init() override;

private:



};