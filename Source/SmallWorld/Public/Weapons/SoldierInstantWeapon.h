#pragma once

#include "CoreMinimal.h"
#include "InstantWeaponClass.h"
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
	UPROPERTY(EditAnywhere)
	float	AttackPoint;

};

class ASoldierPawn;

UCLASS()
class USoldierInstantWeapon : public UObject, public InstantWeaponClass<ASoldierPawn>
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