#pragma once

#include "CoreMinimal.h"
#include "SWrapCompoundWidget.h"
#include "GameFramework/Actor.h"
#include "GameObjectClass.h"
#include "WrapActor.generated.h"


UCLASS()
class UNREALENGINEWRAP_API AWrapActor : public AActor, public GameObjectClass
{
	GENERATED_BODY()

public:
	
	AWrapActor();
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);
	virtual void BeginDestroy() override;


	virtual TSharedPtr<SWidget>	CreateActorDetailWidget() { return SNullWidget::NullWidget; }
	virtual void RefreshView(){}


};