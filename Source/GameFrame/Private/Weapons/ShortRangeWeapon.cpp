#include "ShortRangeWeapon.h"

ShortRangeWeapon::ShortRangeWeapon():
	Damage(0.f)
{

}
ShortRangeWeapon::~ShortRangeWeapon()
{

}
void ShortRangeWeapon::SetDamage(float temDamage)
{
	Damage = std::move(temDamage);
}
float ShortRangeWeapon::GetDamage()
{
	return Damage;
}
