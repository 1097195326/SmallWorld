#include "Archer.h"


AArcher::AArcher()
{
	CurrentWeapon = ProjectileWeapon = NewObject<USoldierProjectileWeapon>();
	ProjectileWeapon->SetOwner(this);
	ProjectileWeapon->AddToRoot();
}
AArcher::~AArcher()
{
	ProjectileWeapon->RemoveFromRoot();
	ProjectileWeapon = nullptr;
}
void AArcher::On_Start() 
{
	ProjectileWeapon->InitWithWeaponInfo(ProjectileWeaponInfo);

}
