#pragma once
#include "PawnBase.h"
#include "WeaponBase.h"

template<typename PawnClass>
class EnableAttackPawn : public PawnBase
{
public:
	EnableAttackPawn(){EnemyPawn = nullptr;}
	~EnableAttackPawn(){EnemyPawn = nullptr;}

	void						SetEnemy(PawnClass * temEnemyPawn){EnemyPawn = temEnemyPawn;}
	PawnClass *					GetEnemy(){return EnemyPawn;}
	void						SetCurrentWeapon(WeaponBase<PawnClass> *	temCurrentWeapon){CurrentWeapon = temCurrentWeapon;}
	WeaponBase<PawnClass> *		GetCurrentWeapon(){return CurrentWeapon;}

	virtual bool				CanAttack() { return false; }
	virtual void				HandleAttack(){}
	virtual void				AttackEnemy(){}

protected:

	WeaponBase<PawnClass> *	CurrentWeapon;

	PawnClass *		EnemyPawn;

};