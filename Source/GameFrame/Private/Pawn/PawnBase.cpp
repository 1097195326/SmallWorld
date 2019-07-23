#include "PawnBase.h"


PawnBase::PawnBase() :
	Health(0.f),
	FieldOfView(0.f),
	FieldOfBody(0.f),
	FieldOfAttack(0.f),
	MaxForce(0.f),
	Mass(0.f)
{

}
PawnBase::~PawnBase()
{

}
bool PawnBase::IsAlive()
{
	return Health <= 0;
}
float PawnBase::CalculateDamage(const float & damage)
{
	return damage;
}
void PawnBase::SetHealth(float health)
{
	Health = std::move(health);

	if (!IsAlive())
	{
		Health = 0.0;
	}
}