#pragma once
#include "BasePawnClass.h"
#include "BaseWeaponClass.h"

template<typename PawnClass>
class EnableAttackPawnClass : public BasePawnClass
{
public:
	EnableAttackPawnClass(){EnemyPawn = nullptr;}
	~EnableAttackPawnClass(){EnemyPawn = nullptr;}

	void						SetEnemy(PawnClass * temEnemyPawn){EnemyPawn = temEnemyPawn;}
	PawnClass *					GetEnemy(){return EnemyPawn;}
	bool						IsHaveEnemy() { return EnemyPawn != nullptr; }
	void						SetCurrentWeapon(BaseWeaponClass<PawnClass> *	temCurrentWeapon){CurrentWeapon = temCurrentWeapon;}
	BaseWeaponClass<PawnClass> *		GetCurrentWeapon(){return CurrentWeapon;}

	virtual bool				CanAttack() { return false; }
	virtual void				HandleAttack(){}
	virtual void				AttackEnemy(){}

protected:

	BaseWeaponClass<PawnClass> *	CurrentWeapon;

	PawnClass *		EnemyPawn;

};