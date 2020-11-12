#pragma once

#include "BaseProjectileClass.h"
#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameConfig.h"
#include "Projectile.generated.h"


USTRUCT()
struct FProjectileInfo
{
	GENERATED_BODY();

	UPROPERTY(EditDefaultsOnly)
		float		HorizontalSpeed;
	UPROPERTY(EditDefaultsOnly)
		float		Damage;
	UPROPERTY(EditDefaultsOnly)
		float		Range;

};

UCLASS()
class AProjectile : public AActor, public BaseProjectileClass
{
	GENERATED_BODY()

public:
	AProjectile();

	virtual void	PostInitializeComponents() override;
	virtual float	GetHorizontalSpeed() override { return ProjectileInfo.HorizontalSpeed; }

	void			SetVelocity(const FVector & velocity);

	UPROPERTY(VisibleDefaultsOnly)
		USphereComponent * CollisionComponent;
	UPROPERTY(VisibleDefaultsOnly)
		UProjectileMovementComponent * MoveComponent;
	UPROPERTY(VisibleDefaultsOnly)
		UStaticMeshComponent * MeshComponent;
	
	UPROPERTY(EditDefaultsOnly , Category = Projectile)
		FProjectileInfo			ProjectileInfo;
	
};
