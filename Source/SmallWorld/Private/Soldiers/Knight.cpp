#include "Knight.h"


AKnight::AKnight()
{
	mSoldierType = S_Knight;

	CurrentWeapon = InstantWeapon = NewObject<USoldierInstantWeapon>();
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