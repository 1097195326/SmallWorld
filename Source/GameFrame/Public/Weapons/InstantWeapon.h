#pragma once
#include "WeaponBase.h"

class GAMEFRAME_API InstantWeapon : public WeaponBase
{
public:
	InstantWeapon();
	~InstantWeapon();

	inline void			SetDamage(float temDamage) { Damage = std::move(temDamage); }
	inline float		GetDamage() { return Damage; }

protected:
	float		Damage;
};