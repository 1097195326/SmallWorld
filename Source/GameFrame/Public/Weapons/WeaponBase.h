#pragma once

#include <utility>

class PawnBase;

template<typename PawnClass>
class WeaponBase
{
public:
	WeaponBase():
		Owner(nullptr),
		StartRange(0.f),
		AttackRange(0.f),
		AttackInterval(0.f)
	{
		
	}
	virtual ~WeaponBase()
	{
		Owner = nullptr;
	}


	// need subClass implement 
	virtual void		AttackEnemy(){}
	virtual bool		IsInRange(PawnClass * temPawn) { return std::move(false); }

	//-----------
	inline void				SetOwner(PawnClass * temOwner) { Owner = temOwner; }
	inline PawnClass *		GetOwner() { return Owner; }
	
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

	PawnClass *			Owner;

	float				StartRange;
	float				AttackRange;

	float				AttackInterval;

};