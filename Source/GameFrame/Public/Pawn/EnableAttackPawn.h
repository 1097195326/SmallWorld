#pragma once
#include "PawnBase.h"
#include "WeaponBase.h"


class EnableAttackPawn : public PawnBase
{
public:
	EnableAttackPawn();
	~EnableAttackPawn();

	void			SetEnemy(PawnBase * temEnemyPawn);
	PawnBase *		GetEnemy();

	virtual void	AttackEnemy();

	void			SetCurrentWeapon(WeaponBase * temWeapon);
protected:
	WeaponBase *	CurrentWeapon;
	PawnBase *		EnemyPawn;

};