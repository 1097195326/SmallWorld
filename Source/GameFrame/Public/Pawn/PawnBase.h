#pragma once
#include "GObject.h"

class PawnBase : public GObject
{
public:
	PawnBase();

	virtual float		CalculateDamage(const float & damage);

	bool				IsAlive();
	void				SetHealth(float health);
	float				GetHealth();
protected:
	float				Health;

};