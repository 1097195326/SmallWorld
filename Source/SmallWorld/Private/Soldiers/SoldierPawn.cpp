#include "SoldierPawn.h"
#include "SoldierPawnController.h"
#include "BaseGroup.h"
#include "GameFramework/DamageType.h"

ASoldierPawn::ASoldierPawn()
{

	AIControllerClass = ASoldierPawnController::StaticClass();

	mLeader = nullptr;
	mEnemy = nullptr;
	mGroup = nullptr;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	SoldierMovement = CreateDefaultSubobject<USoldierPawnMovement>(TEXT("SoldierMovement"));
	SoldierMovement->SetUpdatedComponent(RootComponent);
	
	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);


}
void ASoldierPawn::On_Init()
{
	

}
void ASoldierPawn::On_Start()
{

	
}
void ASoldierPawn::On_Tick(float delta)
{

}
void ASoldierPawn::On_Delete()
{
	mEnemy = nullptr;
	mGroup = nullptr;
	mLeader = nullptr;

}
float ASoldierPawn::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (!IsDieing() && !IsDied())
	{
		float damage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

		fHeath -= damage;
		if (fHeath <= 0.f)
		{
			fHeath = 0.f;
			DieingOn();
		}
		return damage;
	}
	return 0.f;
}
void ASoldierPawn::SetFormationPosition(const FVector & formationPosition)
{
	mFormationPosition = formationPosition;
}
void ASoldierPawn::SetOffsetToLeader(const FVector & offset)
{
	mOffsetToLeader = offset;
}
void ASoldierPawn::SetLeader(ASoldierPawn * leader)
{
	mLeader = leader;
}
float ASoldierPawn::GetDamage()
{

	return fBaseDamage;
}
bool ASoldierPawn::CanAttack()
{
	if (IsHaveEnemy())
	{
		return fFieldOfAttack * fFieldOfAttack > (GetActorLocation() - mEnemy->GetActorLocation()).SizeSquared();
	}
	return false;
}
void ASoldierPawn::Attack()
{
	UGameplayStatics::ApplyDamage(mEnemy, GetDamage(), GetController(), this, UDamageType::StaticClass());


}
// Anim Call End
void ASoldierPawn::AnimAttack()
{

}
void ASoldierPawn::AnimAttackEnd()
{

}
void ASoldierPawn::AnimHitEnd()
{

}
void ASoldierPawn::AnimDieingEnd()
{

}
bool ASoldierPawn::IsHaveEnemy()
{
	if (mEnemy && mEnemy->IsAlive())
	{
		return true;
	}
	return false;
}
bool ASoldierPawn::IsAlive()
{
	return fHeath > 0.f;
}
void ASoldierPawn::AddSteeringForce(FVector Force)
{
	vSteeringForce += Force;
}
FVector ASoldierPawn::SteeringForce()
{
	vSteeringForce = FVector::ZeroVector;

	if (IsSeek())
	{
		vSteeringForce += Seek(vMoveToLocation);
	}
	if (IsArrive())
	{
		vSteeringForce += Arrive(vMoveToLocation);
	}
	return vSteeringForce.GetClampedToMaxSize(fMaxForce);
}
void ASoldierPawn::SetMoveToLocation(FVector Location)
{
	vMoveToLocation = Location;
}
FVector ASoldierPawn::MoveToLocation()
{
	return vMoveToLocation;
}
// ----------------------  behavior tree -------------------

FVector ASoldierPawn::Seek(FVector TargetLocation)
{
	FVector DesiredVelocity = (TargetLocation - GetActorLocation()).GetSafeNormal() * SoldierMovement->MaxSpeed;

	return DesiredVelocity - GetVelocity();
}
FVector ASoldierPawn::Arrive(FVector TargetLocation)
{
	FVector ToTarget = TargetLocation - GetActorLocation();
	if (ToTarget.Size() > 0)
	{
		FVector vv = GetVelocity();
		float speed = ToTarget.Size() / (SoldierMovement->Deceleration * 0.3f);
		speed = FMath::Min(speed, SoldierMovement->MaxSpeed);
		FVector DesiredVelocity = ToTarget.GetSafeNormal() * speed;

		return DesiredVelocity - vv;
	}
	return FVector::ZeroVector;
}
FVector ASoldierPawn::OffsetPursuit(ASoldierPawn * Leader)
{
	FVector ToOffset = mOffsetToLeader - GetActorLocation();

	float LookAheadTime = ToOffset.Size() / (SoldierMovement->MaxSpeed + Leader->GetVelocity().Size());

	return Arrive(mOffsetToLeader + Leader->GetVelocity() * LookAheadTime);
}
FVector ASoldierPawn::Separation(BaseGroup * Group)
{
	FVector Steer = FVector::ZeroVector;
	list<ASoldierPawn*> Soldiers = Group->GetAllSoldier();
	list<ASoldierPawn*>::iterator iter = Soldiers.begin();
	for (; iter != Soldiers.end(); iter++)
	{
		ASoldierPawn * soldier = *iter;
		if (soldier != this)
		{
			FVector ToTarget = GetActorLocation() - soldier->GetActorLocation();
			Steer += ToTarget.GetSafeNormal() / ToTarget.Size();
		}
	}
	return Steer;
}
FVector ASoldierPawn::Alignment(BaseGroup * Group)
{
	FVector AverageHeading = FVector::ZeroVector;
	int    NeighborCount = 0;

	list<ASoldierPawn*> Soldiers = Group->GetAllSoldier();
	list<ASoldierPawn*>::iterator iter = Soldiers.begin();
	for (; iter != Soldiers.end(); iter++)
	{
		ASoldierPawn * soldier = *iter;
		if (soldier != this)
		{
			AverageHeading += soldier->GetActorForwardVector();
			++NeighborCount;
		}
	}
	if (NeighborCount > 0)
	{
		AverageHeading /= NeighborCount;
		AverageHeading -= GetActorForwardVector();
	}
	return AverageHeading;
}
FVector ASoldierPawn::Cohesion(BaseGroup *  Group)
{
	FVector CenterOfMass, Steering;

	int NeighborCount = 0;

	list<ASoldierPawn*> Soldiers = Group->GetAllSoldier();
	list<ASoldierPawn*>::iterator iter = Soldiers.begin();
	for (; iter != Soldiers.end(); iter++)
	{
		ASoldierPawn * soldier = *iter;
		CenterOfMass += soldier->GetActorLocation();
		++NeighborCount;
	}
	if (NeighborCount > 0)
	{
		CenterOfMass /= NeighborCount;
		Steering = Seek(CenterOfMass);
	}
	return Steering;
}