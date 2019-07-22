#include "PawnBase.h"


PawnBase::PawnBase() :
	Health(0.0)
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
float PawnBase::GetHealth()
{
	return Health;
}