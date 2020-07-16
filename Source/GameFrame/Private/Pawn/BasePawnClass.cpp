#include "BasePawnClass.h"


BasePawnClass::BasePawnClass() :
	Health(0.f),
	FieldOfView(0.f),
	FieldOfBody(0.f),
	FieldOfAttack(0.f),
	MaxForce(0.f),
	Mass(0.f)
{

}
bool BasePawnClass::IsAlive()
{
	return Health > 0;
}
float BasePawnClass::CalculateDamage(const float & damage)
{
	return damage;
}
void BasePawnClass::SetHealth(float && health)
{
	Health = std::move(health);

}