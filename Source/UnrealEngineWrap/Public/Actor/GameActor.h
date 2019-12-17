#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GObject.h"
#include "GameActor.generated.h"


UCLASS()
class UNREALENGINEWRAP_API AGameActor : public AActor, public GObject
{
	GENERATED_BODY()

public:
	AGameActor();
	virtual void PostInitializeComponents() override;
	virtual void BeginDestroy() override;
	virtual void Tick(float DeltaSeconds) override;

	virtual void On_Init() override;
	virtual void On_Tick(float DeltaSeconds) override;
	virtual void On_Delete() override;


};