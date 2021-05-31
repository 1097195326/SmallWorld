#pragma once

#include "WrapActor.h"

#include "TargetFlagActor.generated.h"


UCLASS()
class ATargetFlagActor : public AWrapActor
{
public:
	GENERATED_BODY()


		ATargetFlagActor();

	//Begin override AWrapActor
	virtual void On_Init() override;
	virtual void On_Tick(float DeltaSeconds) override;
	virtual void On_Delete() override;

	UPROPERTY(VisibleDefaultsOnly)
		UStaticMeshComponent* MeshComponent;

};
