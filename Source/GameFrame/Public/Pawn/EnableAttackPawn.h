#pragma once
#include "PawnBase.h"
#include "WeaponBase.h"


class GAMEFRAME_API EnableAttackPawn : public PawnBase
{
public:
	EnableAttackPawn();
	~EnableAttackPawn();

	void			SetEnemy(PawnBase * temEnemyPawn);
	PawnBase *		GetEnemy();

	virtual void	AttackEnemy();

protected:

	PawnBase *		EnemyPawn;

};