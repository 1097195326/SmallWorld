#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UserHUD.generated.h"


UCLASS()
class AUserHUD : public AHUD
{
	GENERATED_BODY()
private:
	AUserHUD();

	virtual void BeginPlay() override;
	virtual void DrawHUD() override;

};

