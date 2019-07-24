#include "SoldierProjectileWeapon.h"
#include "SoldierPawn.h"


USoldierProjectileWeapon::USoldierProjectileWeapon()
{

}
USoldierProjectileWeapon::~USoldierProjectileWeapon()
{

}
void USoldierProjectileWeapon::InitWithWeaponInfo(const FProjectileWeaponInfo & weaponInfo)
{

	StartRange = weaponInfo.StartRange;
	AttackRange = weaponInfo.AttackRange;
	AttackInterval = weaponInfo.AttackInterval;
}

void USoldierProjectileWeapon::AttackEnemy()
{

}
bool USoldierProjectileWeapon::IsInRange(ASoldierPawn * temPawn)
{
	ASoldierPawn * OwnerPawn = Cast<ASoldierPawn>(Owner);
	ASoldierPawn * EnemyPawn = Cast<ASoldierPawn>(temPawn);

	if (OwnerPawn && EnemyPawn && AttackRange > 0.f)
	{
		float disSqu = FVector::DistSquared(OwnerPawn->GetActorLocation(), EnemyPawn->GetActorLocation());
		if (disSqu >= StartRange * StartRange && disSqu <= AttackRange * AttackRange)
		{
			return true;
		}
	}
	return false;
}