#pragma once

#include <utility>

class PawnBase;


class GAMEFRAME_API WeaponBase
{
public:
	WeaponBase();
	virtual ~WeaponBase();

	// need subClass implement 
	virtual void		AttackEnemy(){}
	virtual bool		IsInRange(PawnBase * temPawn) { return std::move(false); }

	//-----------
	inline void				SetOwner(PawnBase * temOwner) { Owner = temOwner; }
	inline PawnBase *		GetOwner() { return Owner; }
	
	template<typename T>
	T* GetOwner()
	{
		return Cast<T*>(Owner);
	}
	
	inline void				SetStartRange(float temStartRange) { StartRange = std::move(temStartRange); }
	inline float			GetStartRange() { return StartRange; }
	inline void				SetAttackRange(float temAttackRange) { AttackRange = std::move(temAttackRange); }
	inline float			GetAttackRange() { return AttackRange; }
	inline void				SetAttackInterval(float temAttackInterval) { AttackInterval = std::move(temAttackInterval); }
	inline float			GetAttackInterval() { return AttackInterval; }

protected:

	PawnBase *			Owner;
	float				StartRange;
	float				AttackRange;

	float				AttackInterval;

};