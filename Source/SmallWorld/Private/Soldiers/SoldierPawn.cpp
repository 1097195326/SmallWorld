#include "SoldierPawn.h"
#include "SoldierPawnController.h"
#include "BaseGroup.h"
#include "GameFramework/DamageType.h"

ASoldierPawn::ASoldierPawn()
{

	//AIControllerClass = ASoldierPawnController::StaticClass();
	mLeader = nullptr;
	mEnemy = nullptr;
	mGroup = nullptr;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	SoldierMovement = CreateDefaultSubobject<USoldierPawnMovement>(TEXT("SoldierMovement"));
	SoldierMovement->SetUpdatedComponent(RootComponent);
	
}
void ASoldierPawn::On_Init()
{
	

}
void ASoldierPawn::On_Start()
{
	mController = Cast<ASoldierPawnController>(GetController());
	
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
	if (!mController->IsDieing() && !mController->IsDied())
	{
		float damage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

		fHeath -= damage;
		if (fHeath <= 0.f)
		{
			fHeath = 0.f;
			mController->DieingOn();
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
	UGameplayStatics::ApplyDamage(mEnemy, GetDamage(), mController, this, UDamageType::StaticClass());


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
