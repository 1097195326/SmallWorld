#pragma once

#include "GObject.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GamePawn.generated.h"

UCLASS()
class UNREALENGINEWRAP_API AGamePawn : public APawn , public GObject
{
    GENERATED_BODY()
    
public:
	// feng zhuang APawn ,override AActor Functions 
	virtual void PostInitializeComponents();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void BeginDestroy() override;

public:



};

