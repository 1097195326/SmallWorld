#pragma once

#include "CoreMinimal.h"
#include "SBaseCompoundWidget.h"
#include "GameFramework/Actor.h"
#include "GameObjectClass.h"
#include "GameActor.generated.h"


UCLASS()
class UNREALENGINEWRAP_API AGameActor : public AActor, public GameObjectClass
{
	GENERATED_BODY()

public:
	AGameActor();
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);
	virtual void BeginDestroy() override;


	virtual TSharedPtr<SWidget>	CreateActorDetailWidget() { return SNullWidget::NullWidget; }
	virtual void RefreshView(){}

	
};