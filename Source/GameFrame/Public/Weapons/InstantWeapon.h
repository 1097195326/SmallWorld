#pragma once
#include "WeaponBase.h"


template<typename PawnClass>
class InstantWeapon : public WeaponBase<PawnClass>
{
public:
	
	InstantWeapon() {}
	~InstantWeapon(){}

	inline void			SetDamage(float temDamage) { Damage = std::move(temDamage); }
	inline float		GetDamage() { return Damage; }

protected:
	float		Damage;
};