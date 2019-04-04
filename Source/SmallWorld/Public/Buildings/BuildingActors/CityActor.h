#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StaticPlaneMeshComponent.h"
#include "CityActor.generated.h"

UCLASS()
class ACityActor : public AActor
{
	GENERATED_BODY()

public:
	ACityActor();

	UStaticPlaneMeshComponent * PlaneMeshComponent;

};