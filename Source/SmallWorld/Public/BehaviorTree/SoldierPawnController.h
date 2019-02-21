#pragma once
#include "AIController.h"
#include "SoldierPawn.h"
#include "SoldierPawnController.generated.h"

class UBehaviorTreeComponent;
class UBlackboardComponent;


enum BehaviorType
{
	e_none = 0,
	e_idle = 1,
	e_move = 1 << 1,
	e_attack = 1 << 2,
	e_death = 1 << 3,
};
enum MoveType
{
	e_seek = 1,
	e_arrive = 1 << 1,
	e_offsetpursuit = 1 << 2,
};
enum DeathType
{
	e_dieing = 1,
	e_died = 1 << 1,

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
	void	SetCurrentLocation(FVector Location);
	FVector	CurrentLocation();

	UPROPERTY(VisibleAnywhere)
		ASoldierPawn * SoldierPawn;


private:
	FVector vSteeringForce;
	FVector	vCurrentLocation;

	int		iBehaviorType;
	int		iMoveType;
	int		iAttackType;
	int		iDeathType;

	FVector Seek(FVector TargetLocation);
	FVector Arrive(FVector TargetLocation);
	FVector OffsetPursuit(ASoldierPawn * Leader);

	// beavior func
	FORCEINLINE bool IsIdle() { return (iBehaviorType & e_idle) == e_idle; }
	FORCEINLINE bool IsMove() { return (iBehaviorType & e_move) == e_move; }
	FORCEINLINE bool IsAttack() { return (iBehaviorType & e_attack) == e_attack; }
	FORCEINLINE bool IsDeath() { return (iBehaviorType & e_death) == e_death; }

	FORCEINLINE void IdleOn() { iBehaviorType |= e_idle; }
	FORCEINLINE void MoveOn() { iBehaviorType |= e_move; }
	FORCEINLINE void AttackOn() { iBehaviorType |= e_attack; }
	FORCEINLINE void DeathOn() { iBehaviorType |= e_death; }

	FORCEINLINE void IdleOff() { if (IsIdle()) iBehaviorType ^= e_idle; }
	FORCEINLINE void MoveOff() { if (IsMove()) iBehaviorType ^= e_move; }
	FORCEINLINE void AttackOff() { if (IsAttack()) iBehaviorType ^= e_attack; }
	FORCEINLINE void DeathOff() { if (IsDeath()) iBehaviorType ^= e_death; }
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