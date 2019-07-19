#pragma once
#include "WeaponBase.h"

class ShortRangeWeapon : public WeaponBase
{
public:
	ShortRangeWeapon();
	~ShortRangeWeapon();

	void		SetDamage(float temDamage);
	float		GetDamage();

protected:
	float		Damage;
};