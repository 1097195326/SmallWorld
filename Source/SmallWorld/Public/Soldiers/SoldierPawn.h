#pragma once


#include "GamePawn.h"
#include "SoldierPawnMovement.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Projectile.h"
#include "SoldierPawn.generated.h"

class ASoldierPawnController;
class BaseGroup;

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
protected:
	
	ASoldierPawnController * mController;
	
public:
	
};