#pragma once
#include <utility>


class GAMEFRAME_API PawnBase
{
public:
	PawnBase();
	virtual ~PawnBase();

	virtual float		CalculateDamage(const float & damage);

	bool				IsAlive();
	void				SetHealth(float && health);
	inline float		GetHealth() { return Health; };

	inline void			SetFieldOfView(float temFieldOfView) { FieldOfView = std::move(temFieldOfView); }
	inline float		GetFieldOfView() { return FieldOfView; }
	inline void			SetFieldOfBody(float temFieldOfBody) { FieldOfBody = std::move(temFieldOfBody); }
	inline float		GetFieldOfBody() { return FieldOfBody; }
	inline void			SetFieldOfAttack(float temFieldOfAttack) { FieldOfAttack = std::move(temFieldOfAttack); }
	inline float		GetFieldOfAttack() { return FieldOfAttack; }
	inline void			SetMaxForce(float temMaxForce) { MaxForce = std::move(temMaxForce); }
	inline float		GetMaxForce() { return MaxForce; }
	inline void			SetMass(float temMass) { Mass = std::move(temMass); };
	inline float		GetMass() { return Mass; }

protected:
	float				Health;

	float				FieldOfView;
	float				FieldOfBody;
	float				FieldOfAttack;
	float				MaxForce;
	float				Mass;

};