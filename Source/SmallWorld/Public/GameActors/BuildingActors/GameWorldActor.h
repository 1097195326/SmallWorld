#pragma once

#include "BaseBuildingActor.h"
#include "GameWorldActor.generated.h"


UCLASS()
class AGameWorldActor : public ABaseBuildingActor
{
	GENERATED_BODY()

public:
	AGameWorldActor();

	virtual void On_Init() override;

	virtual TSharedPtr<SWidget>	CreateActorDetailWidget() override;

private:
	UPROPERTY(VisibleDefaultsOnly)
	UBoxComponent * CollisionBox;

};