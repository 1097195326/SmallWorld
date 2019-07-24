#pragma once

#include "CoreMinimal.h"
#include "InstantWeapon.h"
//#include "SoldierPawn.h"
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

class ASoldierPawn;

UCLASS()
class USoldierInstantWeapon : public UObject, public InstantWeapon<ASoldierPawn>
{
	GENERATED_BODY()
public:
	USoldierInstantWeapon();
	~USoldierInstantWeapon();

	void	InitWithWeaponInfo(const FInstantWeaponInfo & weaponInfo);

	// ---- Weapon base----------
	virtual void		AttackEnemy() override;
	virtual bool		IsInRange(ASoldierPawn * temPawn) override;

};