#include "SoldierPawn.h"
#include "SoldierPawnController.h"
#include "SoldierGroup.h"
#include "GameFramework/DamageType.h"

ASoldierPawn::ASoldierPawn()
{
	AIControllerClass = ASoldierPawnController::StaticClass();
	AutoPossessAI = EAutoPossessAI::Spawned;

	mGroup = nullptr;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	mSoldierMovement = CreateDefaultSubobject<USoldierPawnMovement>(TEXT("SoldierMovement"));
	mSoldierMovement->SetUpdatedComponent(RootComponent);
	
	mMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComponent"));
	mMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);


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
void ASoldierPawn::On_End()
{

}
void ASoldierPawn::On_Delete()
{
	mGroup = nullptr;

}
float ASoldierPawn::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (mSoldierState != SoldierState::S_Dieing && mSoldierState != SoldierState::S_Died)
	{
		float damage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

		mHeath -= damage;
		if (mHeath <= 0.f)
		{
			mHeath = 0.f;
		}
		return damage;
	}
	return 0.f;
}
void ASoldierPawn::Attack()
{

}
void ASoldierPawn::SetGroupAndIndex(SoldierGroup * _group,int _index)
{
	mGroup = _group;
	mIndexInGroup = _index;
}
void ASoldierPawn::HaveMoveToGroup()
{
	if (mGroup)
	{
		mGroup->AddGroupNum();
	}
}
FVector ASoldierPawn::GetLocationInGroup()
{
	return mGroup->GetSoldierLocationByIndex(mIndexInGroup);
}
//
//FVector ASoldierPawn::Seek(FVector TargetLocation)
//{
//	FVector DesiredVelocity = (TargetLocation - GetActorLocation()).GetSafeNormal() * SoldierMovement->MaxSpeed;
//
//	return DesiredVelocity - GetVelocity();
//}
//FVector ASoldierPawn::Arrive(FVector TargetLocation)
//{
//	FVector ToTarget = TargetLocation - GetActorLocation();
//	if (ToTarget.Size() > 0)
//	{
//		FVector vv = GetVelocity();
//		float speed = ToTarget.Size() / (SoldierMovement->Deceleration * 0.3f);
//		speed = FMath::Min(speed, SoldierMovement->MaxSpeed);
//		FVector DesiredVelocity = ToTarget.GetSafeNormal() * speed;
//
//		return DesiredVelocity - vv;
//	}
//	return FVector::ZeroVector;
//}
//FVector ASoldierPawn::OffsetPursuit(ASoldierPawn * Leader)
//{
//	FVector ToOffset = mOffsetToLeader - GetActorLocation();
//
//	float LookAheadTime = ToOffset.Size() / (SoldierMovement->MaxSpeed + Leader->GetVelocity().Size());
//
//	return Arrive(mOffsetToLeader + Leader->GetVelocity() * LookAheadTime);
//}
//FVector ASoldierPawn::Separation(SoldierGroup * Group)
//{
//	FVector Steer = FVector::ZeroVector;
//	list<ASoldierPawn*> Soldiers = Group->GetAllSoldier();
//	list<ASoldierPawn*>::iterator iter = Soldiers.begin();
//	for (; iter != Soldiers.end(); iter++)
//	{
//		ASoldierPawn * soldier = *iter;
//		if (soldier != this)
//		{
//			FVector ToTarget = GetActorLocation() - soldier->GetActorLocation();
//			Steer += ToTarget.GetSafeNormal() / ToTarget.Size();
//		}
//	}
//	return Steer;
//}
//FVector ASoldierPawn::Alignment(SoldierGroup * Group)
//{
//	FVector AverageHeading = FVector::ZeroVector;
//	int    NeighborCount = 0;
//
//	list<ASoldierPawn*> Soldiers = Group->GetAllSoldier();
//	list<ASoldierPawn*>::iterator iter = Soldiers.begin();
//	for (; iter != Soldiers.end(); iter++)
//	{
//		ASoldierPawn * soldier = *iter;
//		if (soldier != this)
//		{
//			AverageHeading += soldier->GetActorForwardVector();
//			++NeighborCount;
//		}
//	}
//	if (NeighborCount > 0)
//	{
//		AverageHeading /= NeighborCount;
//		AverageHeading -= GetActorForwardVector();
//	}
//	return AverageHeading;
//}
//FVector ASoldierPawn::Cohesion(SoldierGroup *  Group)
//{
//	FVector CenterOfMass, Steering;
//
//	int NeighborCount = 0;
//
//	list<ASoldierPawn*> Soldiers = Group->GetAllSoldier();
//	list<ASoldierPawn*>::iterator iter = Soldiers.begin();
//	for (; iter != Soldiers.end(); iter++)
//	{
//		ASoldierPawn * soldier = *iter;
//		CenterOfMass += soldier->GetActorLocation();
//		++NeighborCount;
//	}
//	if (NeighborCount > 0)
//	{
//		CenterOfMass /= NeighborCount;
//		Steering = Seek(CenterOfMass);
//	}
//	return Steering;
//}