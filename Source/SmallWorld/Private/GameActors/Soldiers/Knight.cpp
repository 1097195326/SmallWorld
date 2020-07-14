#include "Knight.h"


AKnight::AKnight()
{
	
	CurrentWeapon = InstantWeapon = NewObject<USoldierInstantWeapon>();
	InstantWeapon->SetOwner(this);
	InstantWeapon->AddToRoot();
	
}
AKnight::~AKnight()
{
	InstantWeapon->RemoveFromRoot();
	InstantWeapon = nullptr;
}
void AKnight::On_Start()
{
	
	InstantWeapon->InitWithWeaponInfo(InstantWeaponInfo);

}