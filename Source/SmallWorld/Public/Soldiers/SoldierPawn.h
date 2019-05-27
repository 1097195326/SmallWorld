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

	void			SetGroupAndIndex(SoldierGroup * _group,int _index);
	void			ChangeSoldierState(SoldierState _soldierState);

protected:
	void					HaveMoveToGroup();

	SoldierState			mSoldierState;
	int32					mBehaviorType;
	SoldierType				mSoldierType;
	SoldierGroup *			mGroup;
	int32					mIndexInGroup;

	float					mFieldOfView;
	float					mFieldOfBody;
	float					mFieldOfAttack;
	float					mMaxForce;
	float					mMass;
	float					mHeath;
	float					mBaseDamage;

	float					mAttackInterval;

	UPROPERTY(EditAnywhere)
		UBehaviorTree *				BehaviorTree;
	UPROPERTY(VisibleAnywhere)
		USoldierPawnMovement *		SoldierMovement;
	UPROPERTY(VisibleDefaultsOnly)
		USkeletalMeshComponent *	MeshComponent;
	
	/*FVector					Seek(FVector TargetLocation);
	FVector					Arrive(FVector TargetLocation);
	FVector					OffsetPursuit(ASoldierPawn * Leader);
	FVector					Separation(SoldierGroup *  Group);
	FVector					Alignment(SoldierGroup *  Group);
	FVector					Cohesion(SoldierGroup *  Group);*/

public:
	SoldierType  GetSoldierType() {return mSoldierType;}
	// beavior func

		bool IsHit() { return mSoldierState == S_Hit;}
		bool IsVictory() { return mSoldierState == S_Victory; }
		bool IsIdle() { return mSoldierState == S_Idle; }
		bool IsDieing() { return mSoldierState == S_Dieing; }
		bool IsDied() { return mSoldierState == S_Died; }
	// move func
		
};