#pragma once
#include <utility>

class GAMEFRAME_API ProjectileBase
{
public:
	ProjectileBase();
	virtual ~ProjectileBase();

	inline void			SetHorizontalSpeed(float temSpeed) { HorizontalSpeed = std::move(temSpeed); }
	float				GetHorizontalSpeed() { return HorizontalSpeed; }

protected:
	float		HorizontalSpeed;

};