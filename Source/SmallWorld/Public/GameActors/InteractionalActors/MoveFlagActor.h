#pragma once

#include "GameActor.h"

#include "MoveFlagActor.generated.h"


UCLASS()
class AMoveFlagActor : public AGameActor
{
public:
	GENERATED_BODY()


		AMoveFlagActor();

	//Begin override AGameActor
	virtual void On_Init() override;
	virtual void On_Tick(float DeltaSeconds) override;
	virtual void On_Delete() override;

	UPROPERTY(VisibleDefaultsOnly)
		UInstancedStaticMeshComponent* ForwardMeshComponent;
	/*UPROPERTY(VisibleDefaultsOnly)
		UStaticMeshComponent* BackMeshComponent;
	UPROPERTY(VisibleDefaultsOnly)
		UStaticMeshComponent* LeftMeshComponent;
	UPROPERTY(VisibleDefaultsOnly)
		UStaticMeshComponent* RightMeshComponent;*/
};
