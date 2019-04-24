#pragma once
#include "BaseBuildingActor.h"

#include "TreeStoreActor.generated.h"

UCLASS()
class ATreeStoreActor : public ABaseBuildingActor
{
	GENERATED_BODY()

public:
	ATreeStoreActor();

	virtual void On_Init() override;


};