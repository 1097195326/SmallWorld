#pragma once
#include "BaseWeaponClass.h"


template<typename PawnClass>
class InstantWeaponClass : public BaseWeaponClass<PawnClass>
{
public:
	
	InstantWeaponClass() {}
	~InstantWeaponClass(){}

	inline void			SetDamage(float temDamage) { Damage = std::move(temDamage); }
	inline float		GetDamage() { return Damage; }

protected:
	float		Damage;
};