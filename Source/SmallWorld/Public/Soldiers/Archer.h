#pragma once

#include "SoldierPawn.h"
#include "Archer.generated.h"


UCLASS()
class AArcher : public ASoldierPawn
{
	GENERATED_BODY()

public:
	AArcher();
	~AArcher();


	virtual void On_Start() override;

	UPROPERTY(EditAnywhere)
	FProjectileWeaponInfo	ProjectileWeaponInfo;

	USoldierProjectileWeapon * ProjectileWeapon;

};