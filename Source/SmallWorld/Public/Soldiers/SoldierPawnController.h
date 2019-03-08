#pragma once
#include "AIController.h"
#include "SoldierPawn.h"
#include "BaseGroup.h"
#include "SoldierPawnController.generated.h"

class UBehaviorTreeComponent;
class UBlackboardComponent;


enum BehaviorType
{
	e_normal = 0,
	
	e_idle			= 1,
	//attack
	e_attack		= 1 << 2,
	// death
	e_dieing		= 1 << 3,
	e_died			= 1 << 4,
	// move
	e_seek			= 1 << 5,
	e_arrive		= 1 << 6,
	e_offsetpursuit	= 1 << 7,


};

UCLASS()
class ASoldierPawnController : public AAIController
{
	GENERATED_BODY()
public:
	ASoldierPawnController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	virtual void Possess(APawn* InPawn) override;
	virtual void UnPossess() override;

	void	AddSteeringForce(FVector Force);
	FVector	SteeringForce();
	void	SetMoveToLocation(FVector Location);
	FVector	MoveToLocation();

	UPROPERTY(VisibleAnywhere)
		ASoldierPawn * SoldierPawn;

private:
	FVector vSteeringForce;
	FVector	vMoveToLocation;

	int		iBehaviorType;
	int		iMoveType;
	int		iAttackType;
	int		iDeathType;

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
	FORCEINLINE bool IsSeek() { return (iMoveType & e_seek) == e_seek; }
	FORCEINLINE bool IsArrive() { return (iMoveType & e_arrive) == e_arrive; }
	FORCEINLINE bool IsOffsetPursuit() { return (iMoveType & e_offsetpursuit) == e_offsetpursuit; }

	FORCEINLINE void SeekOn() { iMoveType |= e_seek; }
	FORCEINLINE void ArriveOn() { iMoveType |= e_arrive; }
	FORCEINLINE void OffsetPursuitOn() { iMoveType |= e_offsetpursuit; }

	FORCEINLINE void SeekOff() { if (IsSeek()) iMoveType ^= e_seek; }
	FORCEINLINE void ArriveOff() { if (IsArrive()) iMoveType ^= e_arrive; }
	FORCEINLINE void OffsetPursuitOff() { if (IsOffsetPursuit()) iMoveType ^= e_offsetpursuit; }
};