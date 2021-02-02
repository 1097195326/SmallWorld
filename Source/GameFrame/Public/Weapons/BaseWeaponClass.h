#pragma once

#include <utility>

class BasePawnClass;

template<typename PawnClass>
class BaseWeaponClass
{
public:
	BaseWeaponClass():
		Owner(nullptr),
		StartRange(0.f),
		AttackRange(0.f),
		AttackInterval(0.f),
		CurrentAttackInterval(0.f)
	{
		
	}
	virtual ~BaseWeaponClass()
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

	inline bool IsFullAttackPower() { return CurrentAttackInterval == AttackInterval; }
	void ReturnAttackPower(float InTime)
	{
		CurrentAttackInterval += InTime;
		if (CurrentAttackInterval > AttackInterval)
		{
			CurrentAttackInterval = AttackInterval;
		}
	}

	inline void SetStartRange(float temStartRange) { StartRange = std::move(temStartRange); }
	inline void SetAttackRange(float temAttackRange) { AttackRange = std::move(temAttackRange); }
	inline void SetAttackInterval(float temAttackInterval) { AttackInterval = std::move(temAttackInterval); }
	inline void SetAttackPonit(float temAttackPoint) { AttackPoint = std::move(temAttackPoint); }
	
	inline float GetStartRange() { return StartRange; }
	inline float GetAttackRange() { return AttackRange; }
	inline float GetAttackInterval() { return AttackInterval; }
	inline float GetAttackPonit() { return AttackPoint; }
	inline float GetCurrentAttackInterval() const { return CurrentAttackInterval; }

protected:

	PawnClass * Owner;

	float StartRange;
	float AttackRange;

	float AttackInterval;
	float AttackPoint;
	float CurrentAttackInterval;
};