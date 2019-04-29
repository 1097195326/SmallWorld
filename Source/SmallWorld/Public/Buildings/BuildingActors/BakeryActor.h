#pragma once
#include "BaseBuildingActor.h"
#include "BakeryData.h"

#include "BakeryActor.generated.h"

UCLASS()
class ABakeryActor : public ABaseBuildingActor
{
	GENERATED_BODY()

public:
	ABakeryActor();

	virtual void On_Init() override;


};