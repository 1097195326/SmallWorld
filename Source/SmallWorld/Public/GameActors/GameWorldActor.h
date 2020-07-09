#pragma once


#include "GameActor.h"
#include "GameWorldActor.generated.h"


UCLASS()
class AGameWorldActor : public AGameActor
{
	GENERATED_BODY()

public:
	AGameWorldActor();

	virtual void On_Init() override;
	virtual void On_Tick(float DeltaSeconds) override;
	virtual void On_Delete() override;

	virtual TSharedPtr<SWidget>	CreateActorDetailWidget() override;

private:
	UPROPERTY(VisibleDefaultsOnly)
	UBoxComponent * CollisionBox;

};