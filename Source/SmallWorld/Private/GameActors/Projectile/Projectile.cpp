#include "Projectile.h"

AProjectile::AProjectile()
{
	RootComponent = CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	/*CollisionComponent->SetCollisionObjectType(ProjectileObject);
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
	CollisionComponent->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	CollisionComponent->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);*/

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(RootComponent);

	MoveComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MoveComponent"));
	MoveComponent->SetUpdatedComponent(RootComponent);
}
void AProjectile::PostInitializeComponents()
{
	AActor::PostInitializeComponents();

	ProHorizontalSpeed = ProjectileInfo.HorizontalSpeed;
	ProDamage = ProjectileInfo.Damage;
	ProRange = ProjectileInfo.Range;

}
void AProjectile::SetVelocity(const FVector & velocity)
{
	MoveComponent->Velocity = velocity;

}