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
enum SoldierState
{
	//state
	S_Normal = 0, 
	S_Idle,
	S_FightSelf,
	S_FormationDefense,
	S_FormationFight,
	S_MoveToCity,
	S_MoveToGroup,
	S_ReadyInGroup,
	S_Dieing,
	S_Died,
	S_Hit,
	S_Victory,
};
UENUM()
enum BehaviorType
{
	// move
	B_Normal = 0,
	B_Seek = 1 << 9,
	B_Arrive = 1 << 10,
	B_Offsetpursuit = 1 << 11,

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
	
	void			SetGroupAndIndex(SoldierGroup * _group,int _index);
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
	int32				mIndexInGroup;

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
		bool IsHit() { return (iBehaviorType & S_Hit) == S_Hit;}
	UFUNCTION(BlueprintCallable)
		void HitOn() { iBehaviorType |= S_Hit; }
	UFUNCTION(BlueprintCallable)
		void HitOff() { if (IsHit()) iBehaviorType ^= S_Hit; }
	UFUNCTION(BlueprintCallable)
		bool IsVictory() { return (iBehaviorType & S_Victory) == S_Victory; }
	UFUNCTION(BlueprintCallable)
		void VictoryOn() { iBehaviorType |= S_Victory; }
	UFUNCTION(BlueprintCallable)
		void VictoryOff() { if (IsVictory()) iBehaviorType ^= S_Victory; }
	UFUNCTION(BlueprintCallable)
		bool IsIdle() { return (iBehaviorType & S_Idle) == S_Idle; }
	UFUNCTION(BlueprintCallable)
		void IdleOn() { iBehaviorType |= S_Idle; }
	UFUNCTION(BlueprintCallable)
		bool IsDieing() { return (iBehaviorType & S_Dieing) == S_Dieing; }
	UFUNCTION(BlueprintCallable)
		void DieingOn() { iBehaviorType |= S_Dieing; }
	UFUNCTION(BlueprintCallable)
		void DieingOff() { if (IsDieing()) iBehaviorType ^= S_Dieing; }
	UFUNCTION(BlueprintCallable)
		bool IsDied() { return (iBehaviorType & S_Died) == S_Died; }
	UFUNCTION(BlueprintCallable)
		void DiedOn() { iBehaviorType |= S_Died; }
	UFUNCTION(BlueprintCallable)
		void DiedOff() { if (IsDied()) iBehaviorType ^= S_Died; }
	// move func
	UFUNCTION(BlueprintCallable)
		bool IsSeek() { return (iBehaviorType & B_Seek) == B_Seek; }
	UFUNCTION(BlueprintCallable)
		void SeekOn() { iBehaviorType |= B_Seek; }
	UFUNCTION(BlueprintCallable)
		void SeekOff() { if (IsSeek()) iBehaviorType ^= B_Seek; }
	UFUNCTION(BlueprintCallable)
		bool IsArrive() { return (iBehaviorType & B_Arrive) == B_Arrive; }
	UFUNCTION(BlueprintCallable)
		void ArriveOn() { iBehaviorType |= B_Arrive; }
	UFUNCTION(BlueprintCallable)
		void ArriveOff() { if (IsArrive()) iBehaviorType ^= B_Arrive; }
	UFUNCTION(BlueprintCallable)
		bool IsOffsetPursuit() { return (iBehaviorType & B_Offsetpursuit) == B_Offsetpursuit; }
	UFUNCTION(BlueprintCallable)
		void OffsetPursuitOn() { iBehaviorType |= B_Offsetpursuit; }
	UFUNCTION(BlueprintCallable)
		void OffsetPursuitOff() { if (IsOffsetPursuit()) iBehaviorType ^= B_Offsetpursuit; }
};