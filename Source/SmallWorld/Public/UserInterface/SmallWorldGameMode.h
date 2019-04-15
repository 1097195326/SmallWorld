#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SmallWorldGameMode.generated.h"

UCLASS()
class ASmallWorldGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	ASmallWorldGameMode();

	virtual void StartPlay() override;
	
};

