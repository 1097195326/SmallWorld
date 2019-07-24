#include "EnableAttackPawn.h"



EnableAttackPawn::EnableAttackPawn() :
	EnemyPawn(nullptr)
{

}
EnableAttackPawn::~EnableAttackPawn()
{
	EnemyPawn = nullptr;
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
	
}