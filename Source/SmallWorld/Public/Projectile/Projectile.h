#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Projectile.generated.h"

#define  ProjectileObject ECC_GameTraceChannel1
#define  ProjectileChannel ECC_GameTraceChannel2


UCLASS()
class AProjectile : public AActor
{
	GENERATED_BODY()

public:
	AProjectile();

	UPROPERTY(VisibleDefaultsOnly)
		USphereComponent * CollisionComponent;
	UPROPERTY(VisibleDefaultsOnly)
		UProjectileMovementComponent * MoveComponent;
	UPROPERTY(VisibleDefaultsOnly)
		UStaticMeshComponent * MeshComponent;


};
