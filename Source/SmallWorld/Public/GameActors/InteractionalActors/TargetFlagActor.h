#pragma once

#include "GameActor.h"

#include "TargetFlagActor.generated.h"


UCLASS()
class ATargetFlagActor : public AGameActor
{
public:
	GENERATED_BODY()


		ATargetFlagActor();

	//Begin override AGameActor
	virtual void On_Init() override;
	virtual void On_Tick(float DeltaSeconds) override;
	virtual void On_Delete() override;

	UPROPERTY(VisibleDefaultsOnly)
		UStaticMeshComponent* MeshComponent;

};
