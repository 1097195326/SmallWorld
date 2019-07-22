#include "WeaponBase.h"

#include "PawnBase.h"



WeaponBase::WeaponBase():
	Owner(nullptr),
	StartRange(0.f)
{

}
WeaponBase::~WeaponBase()
{
	Owner = nullptr;
}