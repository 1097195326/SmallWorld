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
	ProjectileClass = weaponInfo.ProjectileClass;
}

void USoldierProjectileWeapon::AttackEnemy()
{
	if (Owner && Owner->IsValidLowLevel() && Owner->IsAlive() && Owner->GetEnemy() && Owner->GetEnemy()->IsValidLowLevel() && Owner->GetEnemy()->IsAlive())
	{
		FVector FireLocation = Owner->GetSpawnProjectileLoction();
		FVector TargetLocation = Owner->GetEnemy()->GetActorLocation() + FVector(0,0,80);

		FTransform transform(FireLocation);

		AProjectile * projectile = Cast<AProjectile>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this, ProjectileClass, transform));
		if (projectile != nullptr)
		{
			float Gravity = projectile->MoveComponent->GetGravityZ();

			FVector2D HorizontalDistance = FVector2D(TargetLocation.X - FireLocation.X, TargetLocation.Y - FireLocation.Y);
			FVector2D HorizontalVelocity = FVector2D(TargetLocation.X - FireLocation.X, TargetLocation.Y - FireLocation.Y).GetSafeNormal() * projectile->GetHorizontalSpeed();
			float AllTime = HorizontalDistance.Size() / projectile->GetHorizontalSpeed();
			float VelocityZ = -(Gravity * AllTime * AllTime * 0.5f - TargetLocation.Z + FireLocation.Z) / AllTime;
			projectile->SetVelocity(FVector(HorizontalVelocity.X, HorizontalVelocity.Y, VelocityZ));

			UGameplayStatics::FinishSpawningActor(projectile, transform);
		}
	}
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