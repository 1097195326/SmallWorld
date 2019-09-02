#pragma once
#include <utility>

class GAMEFRAME_API ProjectileBase
{
public:
	ProjectileBase();
	virtual ~ProjectileBase();

	inline void			SetHorizontalSpeed(float && temSpeed) { ProHorizontalSpeed = std::move(temSpeed); }
	virtual float				GetHorizontalSpeed() { return ProHorizontalSpeed; }

protected:
	float		ProHorizontalSpeed;
	float		ProDamage;
	float		ProRange;

};