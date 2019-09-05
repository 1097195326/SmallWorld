#pragma once
#include "BaseObject.h"


class GAMEFRAME_API ProjectileBase : public BaseObject
{
public:
	ProjectileBase();

	inline void			SetHorizontalSpeed(float && temSpeed) { ProHorizontalSpeed = std::move(temSpeed); }
	virtual float				GetHorizontalSpeed() { return ProHorizontalSpeed; }

protected:
	float		ProHorizontalSpeed;
	float		ProDamage;
	float		ProRange;

};