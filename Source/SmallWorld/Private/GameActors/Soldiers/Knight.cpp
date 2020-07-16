#include "Knight.h"


AKnight::AKnight()
{
	
	CurrentWeapon = InstantWeaponClass = NewObject<USoldierInstantWeapon>();
	InstantWeaponClass->SetOwner(this);
	InstantWeaponClass->AddToRoot();
	
}
AKnight::~AKnight()
{
	InstantWeaponClass->RemoveFromRoot();
	InstantWeaponClass = nullptr;
}
void AKnight::On_Start()
{
	
	InstantWeaponClass->InitWithWeaponInfo(InstantWeaponInfo);

}