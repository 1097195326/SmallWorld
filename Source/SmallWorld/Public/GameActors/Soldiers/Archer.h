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

	// -----------Override Gobject -------------
	virtual void On_Start() override;
	// ----------Override GameActor ---------
	//virtual TSharedPtr<SWidget>	CreateActorDetailWidget() override;

	// ----------- Override EnableAttackPawnClass -----------


	UPROPERTY(EditAnywhere)
	FProjectileWeaponInfo	ProjectileWeaponInfo;

	USoldierProjectileWeapon * ProjectileWeaponClass;

};