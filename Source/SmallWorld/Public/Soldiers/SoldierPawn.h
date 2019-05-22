#pragma once


#include "GamePawn.h"
#include "SoldierPawnMovement.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Components/SkeletalMeshComponent.h"
#include "Projectile.h"
#include "SoldierBaseState.h"

#include "SoldierPawn.generated.h"

class SoldierGroup;

UENUM()
enum BehaviorType
{
	e_normal = 0,
	//state
	e_idle = 1,
	e_attack = 1 << 2,
	e_dieing = 1 << 3,
	e_died = 1 << 4,
	e_hit = 1 << 5,
	e_victory = 1 << 6,
	e_walk = 1 << 7,
	e_run = 1 << 8,
	// move
	e_seek = 1 << 9,
	e_arrive = 1 << 10,
	e_offsetpursuit = 1 << 11,

};
UENUM()
enum SoldierType
{
	S_Archer,
	S_Footman,
	S_Griffin,
	S_Horseman,
	S_Knight,
	S_Mage,
	S_SiegeEngine,
};

UCLASS()
class ASoldierPawn : public AGamePawn
{
	GENERATED_BODY()
public:
	ASoldierPawn();

	virtual void	On_Init() override;
	virtual void	On_Start() override;
	virtual void	On_Tick(float delta) override;
	virtual void	On_End() override;
	virtual void	On_Delete() override;

	virtual float	TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void	Attack();

	void			SetFormationPosition(const FVector & formationPosition);
	void			SetOffsetToLeader(const FVector & offset);
	void			SetLeader(ASoldierPawn * leader);
	
	void			SetGroup(SoldierGroup * _group);
	void			ChangeSoldierState(SoldierBaseState * _soldierState);

	float			GetDamage();
	bool			CanAttack();
	bool			IsHaveEnemy();
	bool			IsAlive();

	void			AddSteeringForce(FVector Force);
	FVector			SteeringForce();
	void			SetMoveToLocation(FVector Location);
	FVector			MoveToLocation();

	UFUNCTION(BlueprintCallable)
		void		AnimAttack();
	UFUNCTION(BlueprintCallable)
		void		AnimAttackEnd();
	UFUNCTION(BlueprintCallable)
		void		AnimHitEnd();
	UFUNCTION(BlueprintCallable)
		void		AnimDieingEnd();
public:
	SoldierType			mSoldierType;
	FVector				mFormationPosition;
	FVector				mOffsetToLeader;
	ASoldierPawn *		mLeader;
	ASoldierPawn *		mEnemy;
	SoldierGroup *		mGroup;

	UPROPERTY(EditAnywhere, Category = Soldier)
		float			fFieldOfView;
	UPROPERTY(EditAnywhere, Category = Soldier)
		float			fFieldOfBody;
	UPROPERTY(EditAnywhere, Category = Soldier)
		float			fFieldOfAttack;
	UPROPERTY(EditAnywhere, Category = Soldier)
		float			fMaxForce;
	UPROPERTY(EditAnywhere, Category = Soldier)
		float			fMass;
	UPROPERTY(EditAnywhere, Category = Soldier)
		float			fHeath;
	UPROPERTY(EditAnywhere, Category = Soldier)
		float			fBaseDamage;
	UPROPERTY(EditAnywhere, Category = Soldier)
		float			fAttackInterval;

	UPROPERTY(EditAnywhere)
		UBehaviorTree *				BehaviorTree;
	UPROPERTY(VisibleAnywhere)
		USoldierPawnMovement *		SoldierMovement;
	UPROPERTY(VisibleDefaultsOnly)
		USkeletalMeshComponent *	MeshComponent;
	

protected:
	void					HaveMoveToGroup();

	SoldierBaseState *				mSoldierState;

	FVector					vSteeringForce;
	FVector					vMoveToLocation;

	int						iBehaviorType;

	FVector					Seek(FVector TargetLocation);
	FVector					Arrive(FVector TargetLocation);
	FVector					OffsetPursuit(ASoldierPawn * Leader);
	FVector					Separation(SoldierGroup *  Group);
	FVector					Alignment(SoldierGroup *  Group);
	FVector					Cohesion(SoldierGroup *  Group);

public:
	// beavior func

	UFUNCTION(BlueprintCallable)
		bool IsRun() { return (iBehaviorType & e_run) == e_run; }
	UFUNCTION(BlueprintCallable)
		void RunOn() { iBehaviorType |= e_run; }
	UFUNCTION(BlueprintCallable)
		void RunOff() { if (IsRun()) iBehaviorType ^= e_run; }
	UFUNCTION(BlueprintCallable)
		bool IsWalk() { return (iBehaviorType & e_walk) == e_walk; }
	UFUNCTION(BlueprintCallable)
		void WalkOn() { iBehaviorType |= e_walk; }
	UFUNCTION(BlueprintCallable)
		void WalkOff() { if (IsWalk()) iBehaviorType ^= e_walk; }
	UFUNCTION(BlueprintCallable)
		bool IsHit() { return (iBehaviorType & e_hit) == e_hit;}
	UFUNCTION(BlueprintCallable)
		void HitOn() { iBehaviorType |= e_hit; }
	UFUNCTION(BlueprintCallable)
		void HitOff() { if (IsHit()) iBehaviorType ^= e_hit; }
	UFUNCTION(BlueprintCallable)
		bool IsVictory() { return (iBehaviorType & e_victory) == e_victory; }
	UFUNCTION(BlueprintCallable)
		void VictoryOn() { iBehaviorType |= e_victory; }
	UFUNCTION(BlueprintCallable)
		void VictoryOff() { if (IsVictory()) iBehaviorType ^= e_victory; }
	UFUNCTION(BlueprintCallable)
		bool IsIdle() { return (iBehaviorType & e_idle) == e_idle; }
	UFUNCTION(BlueprintCallable)
		void IdleOn() { iBehaviorType |= e_idle; }
	UFUNCTION(BlueprintCallable)
		void IdleOff() { if (IsIdle()) iBehaviorType ^= e_idle; }
	UFUNCTION(BlueprintCallable)
		bool IsAttack() { return (iBehaviorType & e_attack) == e_attack; }
	UFUNCTION(BlueprintCallable)
		void AttackOn() { iBehaviorType |= e_attack; }
	UFUNCTION(BlueprintCallable)
		void AttackOff() { if (IsAttack()) iBehaviorType ^= e_attack; }
	UFUNCTION(BlueprintCallable)
		bool IsDieing() { return (iBehaviorType & e_dieing) == e_dieing; }
	UFUNCTION(BlueprintCallable)
		void DieingOn() { iBehaviorType |= e_dieing; }
	UFUNCTION(BlueprintCallable)
		void DieingOff() { if (IsDieing()) iBehaviorType ^= e_dieing; }
	UFUNCTION(BlueprintCallable)
		bool IsDied() { return (iBehaviorType & e_died) == e_died; }
	UFUNCTION(BlueprintCallable)
		void DiedOn() { iBehaviorType |= e_died; }
	UFUNCTION(BlueprintCallable)
		void DiedOff() { if (IsDied()) iBehaviorType ^= e_died; }
	// move func
	UFUNCTION(BlueprintCallable)
		bool IsSeek() { return (iBehaviorType & e_seek) == e_seek; }
	UFUNCTION(BlueprintCallable)
		void SeekOn() { iBehaviorType |= e_seek; }
	UFUNCTION(BlueprintCallable)
		void SeekOff() { if (IsSeek()) iBehaviorType ^= e_seek; }
	UFUNCTION(BlueprintCallable)
		bool IsArrive() { return (iBehaviorType & e_arrive) == e_arrive; }
	UFUNCTION(BlueprintCallable)
		void ArriveOn() { iBehaviorType |= e_arrive; }
	UFUNCTION(BlueprintCallable)
		void ArriveOff() { if (IsArrive()) iBehaviorType ^= e_arrive; }
	UFUNCTION(BlueprintCallable)
		bool IsOffsetPursuit() { return (iBehaviorType & e_offsetpursuit) == e_offsetpursuit; }
	UFUNCTION(BlueprintCallable)
		void OffsetPursuitOn() { iBehaviorType |= e_offsetpursuit; }
	UFUNCTION(BlueprintCallable)
		void OffsetPursuitOff() { if (IsOffsetPursuit()) iBehaviorType ^= e_offsetpursuit; }
};