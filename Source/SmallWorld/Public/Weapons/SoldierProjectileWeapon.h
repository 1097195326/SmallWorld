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

UCLASS()
class USoldierProjectileWeapon : public UObject, public ProjectileWeapon
{
	GENERATED_BODY()

public:
	USoldierProjectileWeapon();

	UPROPERTY(EditAnywhere)
		FProjectileWeaponInfo	ProjectileWeaponInfo;

};