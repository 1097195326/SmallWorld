#pragma once
#include "BaseBuildingActor.h"
#include "ArmyCenterData.h"

#include "ArmyCenterActor.generated.h"

UCLASS()
class AArmyCenterActor : public ABaseBuildingActor
{
	GENERATED_BODY()

public:
	AArmyCenterActor();

	// ------------- Override GObject ------------
	virtual void On_Init() override;
	// ----------- Override GameActor ----------
	virtual TSharedPtr<SWidget>	CreateActorDetailWidget() override;

};