#pragma once

#include "CoreMinimal.h"
#include "InstantWeapon.h"
#include "SoldierInstantWeapon.generated.h"

USTRUCT()
struct FInstantWeaponInfo
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
class USoldierInstantWeapon : public UObject, public InstantWeapon
{
	GENERATED_BODY()
public:
	USoldierInstantWeapon();
	~USoldierInstantWeapon();

	void	InitWithWeaponInfo(const FInstantWeaponInfo & weaponInfo);

	
};