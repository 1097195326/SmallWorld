#pragma once
#include "BaseBuildingActor.h"

#include "TreeActor.generated.h"

UCLASS()
class ATreeActor : public ABaseBuildingActor
{
	GENERATED_BODY()

public:
	ATreeActor();

	virtual void On_Init() override;


};