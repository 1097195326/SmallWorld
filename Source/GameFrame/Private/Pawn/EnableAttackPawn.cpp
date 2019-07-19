#include "EnableAttackPawn.h"



EnableAttackPawn::EnableAttackPawn() :
	CurrentWeapon(nullptr),
	EnemyPawn(nullptr)
{

}
EnableAttackPawn::~EnableAttackPawn()
{
	EnemyPawn = nullptr;
	if (CurrentWeapon)
	{
		delete CurrentWeapon;
	}
}
void EnableAttackPawn::SetEnemy(PawnBase * temEnemyPawn)
{
	EnemyPawn = temEnemyPawn;
}
PawnBase * EnableAttackPawn::GetEnemy()
{
	return EnemyPawn;
}
void EnableAttackPawn::AttackEnemy()
{
	if (CurrentWeapon)
	{
		CurrentWeapon->AttackEnemy();
	}
}
void EnableAttackPawn::SetCurrentWeapon(WeaponBase * temWeapon)
{
	CurrentWeapon = temWeapon;
}