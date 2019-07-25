#include "SoldierInstantWeapon.h"

#include "SoldierPawn.h"


USoldierInstantWeapon::USoldierInstantWeapon()
{

}
USoldierInstantWeapon::~USoldierInstantWeapon()
{

}
void USoldierInstantWeapon::InitWithWeaponInfo(const FInstantWeaponInfo & weaponInfo)
{
	Damage = weaponInfo.Damage;
	StartRange = weaponInfo.StartRange;
	AttackRange = weaponInfo.AttackRange;
	AttackInterval = weaponInfo.AttackInterval;
}

void USoldierInstantWeapon::AttackEnemy()
{
	UGameplayStatics::ApplyDamage(Owner->GetEnemy(), Damage, Owner->GetController(), Owner, UDamageType::StaticClass());

}
bool USoldierInstantWeapon::IsInRange(ASoldierPawn * temPawn)
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