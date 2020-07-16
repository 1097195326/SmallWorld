#include "Archer.h"


AArcher::AArcher()
{
	CurrentWeapon = ProjectileWeaponClass = NewObject<USoldierProjectileWeapon>();
	ProjectileWeaponClass->SetOwner(this);
	ProjectileWeaponClass->AddToRoot();
}
AArcher::~AArcher()
{
	ProjectileWeaponClass->RemoveFromRoot();
	ProjectileWeaponClass = nullptr;
}
void AArcher::On_Start() 
{
	ProjectileWeaponClass->InitWithWeaponInfo(ProjectileWeaponInfo);

}
