#pragma once

#include "WrapActor.h"

#include "MoveFlagActor.generated.h"


UCLASS()
class AMoveFlagActor : public AWrapActor
{
public:
	GENERATED_BODY()


		AMoveFlagActor();

	//Begin override AWrapActor
	virtual void On_Init() override;
	virtual void On_Tick(float DeltaSeconds) override;
	virtual void On_Delete() override;

	UPROPERTY(VisibleDefaultsOnly)
		UInstancedStaticMeshComponent* MeshComponent;
	
};
