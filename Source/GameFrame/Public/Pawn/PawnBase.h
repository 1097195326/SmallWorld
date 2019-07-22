#pragma once

class GAMEFRAME_API PawnBase
{
public:
	PawnBase();
	virtual ~PawnBase();

	virtual float		CalculateDamage(const float & damage);

	bool				IsAlive();
	void				SetHealth(float health);
	float				GetHealth();
protected:
	float				Health;

};