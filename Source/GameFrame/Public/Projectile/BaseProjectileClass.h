#pragma once
#include "BaseObjectClass.h"


class GAMEFRAME_API BaseProjectileClass : public BaseObjectClass
{
public:
	BaseProjectileClass();

	inline void			SetHorizontalSpeed(float && temSpeed) { ProHorizontalSpeed = std::move(temSpeed); }
	virtual float				GetHorizontalSpeed() { return ProHorizontalSpeed; }

protected:
	float		ProHorizontalSpeed;
	float		ProDamage;
	float		ProRange;

};