#pragma once

#include "CoreMinimal.h"
#include "ProjectileWeapon.h"
#include "SoldierProjectileWeapon.generated.h"


USTRUCT()
struct FProjectileWeaponInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
		float	Damage;
	UPROPERTY(EditAnywhere)
		float	StartRange;
	UPROPERTY(EditAnywhere)
		float	AttackRange;
	UPROPERTY(EditAnywhere)
		float	AttackInterval;

};
class ASoldierPawn;

UCLASS()
class USoldierProjectileWeapon : public UObject, public ProjectileWeapon<ASoldierPawn>
{
	GENERATED_BODY()

public:
	USoldierProjectileWeapon();
	~USoldierProjectileWeapon();

	// ---- Weapon base----------
	virtual void		AttackEnemy() override;
	virtual bool		IsInRange(ASoldierPawn * temPawn) override;

	// self
	void	InitWithWeaponInfo(const FProjectileWeaponInfo & weaponInfo);

};