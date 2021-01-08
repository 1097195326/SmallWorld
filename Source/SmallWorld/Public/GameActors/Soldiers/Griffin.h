#pragma once

#include "SoldierPawn.h"
#include "Griffin.generated.h"


UCLASS()
class AGriffin : public ASoldierPawn
{
	GENERATED_BODY()

public:
	AGriffin();
	virtual bool TryMoveSoldier() override;

};