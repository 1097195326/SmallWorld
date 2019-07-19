#include "WeaponBase.h"

#include "PawnBase.h"



WeaponBase::WeaponBase():
	Owner(nullptr)
{

}
WeaponBase::~WeaponBase()
{
	Owner = nullptr;
}
void WeaponBase::AttackEnemy()
{

}
void WeaponBase::SetOwner(PawnBase * temOwner)
{
	Owner = temOwner;
}
PawnBase * WeaponBase::GetOwner()
{
	return Owner;
}