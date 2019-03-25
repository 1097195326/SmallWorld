#pragma once


#include "GamePawn.h"
#include "SoldierPawnMovement.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Components/SkeletalMeshComponent.h"
#include "Projectile.h"
#include "SoldierPawn.generated.h"

class BaseGroup;


enum BehaviorType
{
	e_normal = 0,

	e_idle = 1,
	//attack
	e_attack = 1 << 2,
	// death
	e_dieing = 1 << 3,
	e_died = 1 << 4,
	// move
	e_seek = 1 << 5,
	e_arrive = 1 << 6,
	e_offsetpursuit = 1 << 7,


};


UCLASS()
class ASoldierPawn : public AGamePawn
{
	GENERATED_BODY()
public:
	ASoldierPawn();

	virtual void On_Init() override;
	virtual void On_Start() override;
	virtual void On_Tick(float delta) override;
	virtual void On_Delete() override;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void	Attack();

	void SetFormationPosition(const FVector & formationPosition);
	void SetOffsetToLeader(const FVector & offset);
	void SetLeader(ASoldierPawn * leader);
	

	float GetDamage();
	bool	CanAttack();
	bool	IsHaveEnemy();
	bool	IsAlive();

public:
	FVector mFormationPosition;
	FVector mOffsetToLeader;
	ASoldierPawn * mLeader;
	ASoldierPawn * mEnemy;
	BaseGroup * mGroup;

	UPROPERTY(EditAnywhere, Category = Soldier)
		float	fFieldOfView;
	UPROPERTY(EditAnywhere, Category = Soldier)
		float	fFieldOfBody;
	UPROPERTY(EditAnywhere, Category = Soldier)
		float	fFieldOfAttack;
	UPROPERTY(EditAnywhere, Category = Soldier)
		float	fMaxForce;
	UPROPERTY(EditAnywhere, Category = Soldier)
		float	fMass;
	UPROPERTY(EditAnywhere, Category = Soldier)
		float	fHeath;
	UPROPERTY(EditAnywhere, Category = Soldier)
		float	fBaseDamage;
	UPROPERTY(EditAnywhere, Category = Soldier)
		float	fAttackInterval;

	UPROPERTY(EditAnywhere)
		UBehaviorTree * BehaviorTree;
	UPROPERTY(VisibleAnywhere)
		USoldierPawnMovement * SoldierMovement;
	UPROPERTY(VisibleDefaultsOnly)
		USkeletalMeshComponent * MeshComponent;
	
public:
	void	AddSteeringForce(FVector Force);
	FVector	SteeringForce();
	void	SetMoveToLocation(FVector Location);
	FVector	MoveToLocation();

private:
	FVector vSteeringForce;
	FVector	vMoveToLocation;

	int iBehaviorType;

	FVector Seek(FVector TargetLocation);
	FVector Arrive(FVector TargetLocation);
	FVector OffsetPursuit(ASoldierPawn * Leader);
	FVector Separation(BaseGroup *  Group);
	FVector Alignment(BaseGroup *  Group);
	FVector Cohesion(BaseGroup *  Group);

public:
	// beavior func
	FORCEINLINE bool IsIdle() { return (iBehaviorType & e_idle) == e_idle; }
	FORCEINLINE bool IsAttack() { return (iBehaviorType & e_attack) == e_attack; }

	FORCEINLINE void IdleOn() { iBehaviorType |= e_idle; }
	FORCEINLINE void AttackOn() { iBehaviorType |= e_attack; }

	FORCEINLINE void IdleOff() { if (IsIdle()) iBehaviorType ^= e_idle; }
	FORCEINLINE void AttackOff() { if (IsAttack()) iBehaviorType ^= e_attack; }
	// death
	FORCEINLINE bool IsDieing() { return (iBehaviorType & e_dieing) == e_dieing; }
	FORCEINLINE bool IsDied() { return (iBehaviorType & e_died) == e_died; }

	FORCEINLINE void DieingOn() { iBehaviorType |= e_dieing; }
	FORCEINLINE void DiedOn() { iBehaviorType |= e_died; }

	FORCEINLINE void DieingOff() { if (IsDieing()) iBehaviorType ^= e_dieing; }
	FORCEINLINE void DiedOff() { if (IsDied()) iBehaviorType ^= e_died; }
	// move func
	FORCEINLINE bool IsSeek() { return (iBehaviorType & e_seek) == e_seek; }
	FORCEINLINE bool IsArrive() { return (iBehaviorType & e_arrive) == e_arrive; }
	FORCEINLINE bool IsOffsetPursuit() { return (iBehaviorType & e_offsetpursuit) == e_offsetpursuit; }

	FORCEINLINE void SeekOn() { iBehaviorType |= e_seek; }
	FORCEINLINE void ArriveOn() { iBehaviorType |= e_arrive; }
	FORCEINLINE void OffsetPursuitOn() { iBehaviorType |= e_offsetpursuit; }

	FORCEINLINE void SeekOff() { if (IsSeek()) iBehaviorType ^= e_seek; }
	FORCEINLINE void ArriveOff() { if (IsArrive()) iBehaviorType ^= e_arrive; }
	FORCEINLINE void OffsetPursuitOff() { if (IsOffsetPursuit()) iBehaviorType ^= e_offsetpursuit; }
};