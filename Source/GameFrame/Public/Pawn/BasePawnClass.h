#pragma once
#include "BaseObjectClass.h"


class GAMEFRAME_API BasePawnClass : public BaseObjectClass
{
public:
	BasePawnClass();

	virtual float CalculateDamage(const float & damage) { return 0.f; }

	virtual bool IsAlive() { return true; }

	virtual void SetHealth(float && health){}
	virtual void SetFieldOfView(float temFieldOfView) {}
	virtual void SetFieldOfBody(float temFieldOfBody) {}
	virtual void SetFieldOfAttack(float temFieldOfAttack) {}
	virtual void SetMaxForce(float temMaxForce) {}
	virtual void SetMass(float temMass) {};

	virtual float GetHealth() { return 0.f; }
	virtual float GetFieldOfView() { return 0.f; }
	virtual float GetFieldOfBody() { return 0.f;}
	virtual float GetFieldOfAttack() { return 0.f; }
	virtual float GetMaxForce() { return 0.f; }
	virtual float GetMass() { return 0.f;}

protected:

};