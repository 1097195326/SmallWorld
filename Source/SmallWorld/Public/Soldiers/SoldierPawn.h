#pragma once

#include "GamePawn.h"
#include "SoldierPawnMovement.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Components/SkeletalMeshComponent.h"
#include "Projectile.h"
#include "EnableAttackPawn.h"
#include "SoldierInstantWeapon.h"
#include "SoldierProjectileWeapon.h"
#include "SoldierPawn.generated.h"

class SoldierGroup;

UENUM()
enum class SoldierState : uint32
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
enum SoldierAnimState 
{
	Anim_Idle = 1,
	Anim_Attack1,
	Anim_Attack2,
	Anim_Death,
	Anim_Hit,
	Anim_Run,
	Anim_Walk,
	Anim_Victory,
};
UENUM()
enum BehaviorType
{
	// move
	B_Normal = 0,
	B_Seek = 1 << 0,
	B_Arrive = 1 << 1,
	B_Offsetpursuit = 1 << 2,

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
class ASoldierPawn : public AGamePawn, public EnableAttackPawn<ASoldierPawn>
{
	GENERATED_BODY()
public:
	ASoldierPawn();
	// --------- Override GObject --------------
	virtual void	On_Init() override;
	virtual void	On_Start() override;
	virtual void	On_Tick(float delta) override;
	virtual void	On_End() override;
	virtual void	On_Delete() override;
	// ------------ Override APawn ----------
	virtual float	TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	
	//------- Override EanbleAttackPawn
	virtual void	AttackEnemy() override;
	virtual bool	CanAttack()override;
	virtual void	HandleAttack() override;

	void			SetGroupAndIndex(SoldierGroup * _group,int _index);
	
	// --------- SoldierSate ------------
	FORCEINLINE SoldierState	GetSoldierState() { return mSoldierState; }
	FORCEINLINE void			ChangeSoldierState(SoldierState _state) { mSoldierState = _state; }
	FORCEINLINE bool			IsInState(SoldierState _state) { return mSoldierState == _state; }

	FORCEINLINE SoldierType			GetSoldierType() { return mSoldierType; }
	FORCEINLINE	UBehaviorTree *		GetBehaviorTree() { return mBehaviorTree; }

	FVector							GetLocationInGroup();

	void							ToGroupForward();
	FORCEINLINE void						SetSoldierAnimState(SoldierAnimState _state) { mSoldierAnimState = _state; }
	
	UFUNCTION(BlueprintCallable)
	SoldierAnimState						GetSoldierAnimState() { return mSoldierAnimState; }

	FVector			GetSpawnProjectileLoction();

protected:
	

	void					HaveMoveToGroup();

	UPROPERTY(EditAnywhere)
		UBehaviorTree *				mBehaviorTree;
	UPROPERTY(VisibleAnywhere)
		USoldierPawnMovement *		mSoldierMovement;
	UPROPERTY(VisibleDefaultsOnly)
		USkeletalMeshComponent *	mMeshComponent;

	SoldierAnimState		mSoldierAnimState;
	SoldierState			mSoldierState;
	SoldierType				mSoldierType;
	int32					mBehaviorType;
	int32					mIndexInGroup;
	SoldierGroup *			mGroup;

private:
	float					LastAttackTime;

	
	
	/*FVector					Seek(FVector TargetLocation);
	FVector					Arrive(FVector TargetLocation);
	FVector					OffsetPursuit(ASoldierPawn * Leader);
	FVector					Separation(SoldierGroup *  Group);
	FVector					Alignment(SoldierGroup *  Group);
	FVector					Cohesion(SoldierGroup *  Group);*/


};