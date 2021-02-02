#include "SoldierPawn.h"
#include "SoldierPawnController.h"
#include "SoldierGroup.h"
#include "GameFramework/DamageType.h"
#include "BaseSoldierDataClass.h"
#include "GroundTileActor.h"
#include "GameManager.h"
#include "Kismet/KismetMathLibrary.h"

ASoldierPawn::ASoldierPawn():
	LastAttackTime(0.f)
{
	AIControllerClass = ASoldierPawnController::StaticClass();
	AutoPossessAI = EAutoPossessAI::Spawned;
	
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Block);
	GetCapsuleComponent()->SetCollisionResponseToChannel(SoldierTrace, ECR_Ignore);
	GetCapsuleComponent()->SetCollisionObjectType(SoldierTrace);

	bUseControllerRotationYaw = true;
	PrimaryActorTick.bCanEverTick = true;


	mGroup = nullptr;
	OriginGroundTile = nullptr;
	TargetGroundTile = nullptr;

	//CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	//
	//RootComponent = CapsuleComponent;
	//
	////RootComponent = SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));

	//SoldierMovement = CreateDefaultSubobject<USoldierPawnMovement>(TEXT("SoldierMovement"));
	//SoldierMovement->SetUpdatedComponent(RootComponent);

	///*CharacterMovement = CreateDefaultSubobject<UCharacterMovementComponent>(TEXT("CharacterMovement"));
	//CharacterMovement->SetUpdatedComponent(RootComponent);*/
	//
	//MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComponent"));
	//MeshComponent->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPose;
	//MeshComponent->PrimaryComponentTick.TickGroup = TG_PrePhysics;
	////MeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	//MeshComponent->SetupAttachment(RootComponent);
}
void ASoldierPawn::On_Init()
{
	
}
void ASoldierPawn::On_Start()
{
	
}
void ASoldierPawn::On_Tick(float delta)
{
	if (SoldierData->IsAlive())
	{
		if (!SoldierData->IsFullMovability())
		{
			SoldierData->ReturnMovability(delta);
		}
		if (!SoldierData->IsFullHealth())
		{
			SoldierData->ReturnHealth(delta);
		}
		if (!GetCurrentWeapon()->IsFullAttackPower())
		{
			GetCurrentWeapon()->ReturnAttackPower(delta);
		}
		if (!SoldierData->IsUserData())
		{
			UpdateAI(delta);
		}
	}
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

		SoldierData->TakeDamage(damage);
		if (!SoldierData->IsAlive())
		{
			ASoldierPawnController * MyController = Cast<ASoldierPawnController>(Controller);
			if (MyController)
			{
				UBehaviorTreeComponent * BehaviorTreeCom = Cast<UBehaviorTreeComponent>(MyController->GetBrainComponent());
				if (BehaviorTreeCom)
				{
					BehaviorTreeCom->StopTree();
				}
				MyController->StopMovement();
			}
			mSoldierState = SoldierState::S_Dieing;
			mSoldierAnimState = Anim_Death;
		}
		return damage;
	}
	return 0.f;
}
void ASoldierPawn::DeathCallBack()
{
	mSoldierState = SoldierState::S_Died;
	GetWorld()->GetTimerManager().SetTimer(DeathTimerHandle, this, &ASoldierPawn::PendingDestory, 5.f, false);
}
void ASoldierPawn::PendingDestory()
{
	BeginDestroy();
}
bool ASoldierPawn::CanAttack()
{
	float currentTime = GetWorld()->TimeSeconds;

	if (currentTime >= LastAttackTime + CurrentWeapon->GetAttackInterval() && CurrentWeapon->IsInRange(EnemyPawn))
	{
		return true;
	}
	return false;
}
bool ASoldierPawn::IsAlive()
{
	return SoldierData->IsAlive();
}
void ASoldierPawn::AttackEnemy()
{
	CurrentWeapon->AttackEnemy();

}
void ASoldierPawn::HandleAttack()
{
	//CurrentWeapon->AttackEnemy();

}
void ASoldierPawn::SetSelected(bool InSlelect)
{
	if (InSlelect)
	{
		  //GetWorld()->SpawnActor<AStaticMeshActor>();

	}
	else
	{

	}
}
bool ASoldierPawn::IsEnemy(ASoldierPawn * InSoldier)
{
	HordeDataClass * InHordeData = InSoldier->GetSoldierData()->GetHordeData();
	HordeDataClass * SelfHordeData = GetSoldierData()->GetHordeData();

	return InHordeData != SelfHordeData;
}
TSharedPtr<SWidget>	ASoldierPawn::CreateActorDetailWidget()
{

	return SNullWidget::NullWidget;
}
void ASoldierPawn::RefreshView()
{
	
}
void ASoldierPawn::UpdateAI(float delta)
{
	if (SoldierData->IsFullMovability())
	{
		ASoldierPawnController * TemController = Cast<ASoldierPawnController>(Controller);
		if (TryMoveSoldier())
		{
			SoldierData->ConsumeMovability();
		}
	}
	if (SoldierData->IsFullHealth())
	{

	}
	if (GetCurrentWeapon()->IsFullAttackPower())
	{

	}

}
bool ASoldierPawn::TryMoveSoldier()
{
	int32 MoveDis = GetSoldierData()->GetMoveRange();
	AGroundTileActor* MainTile = GetOriginGroundTile();
	TArray<AGroundTileActor*>  AroundTiles;
	GameManager::GetGroundTileAroundSoldier(MainTile, MoveDis, AroundTiles);
	if (AroundTiles.Num() > 0)
	{
		int32 TileIndex = UKismetMathLibrary::RandomInteger(AroundTiles.Num());
		AGroundTileActor * TileActor = AroundTiles[TileIndex];
		TargetGroundTile = TileActor;
		OriginGroundTile->SetBusy(true);
		TargetGroundTile->SetBusy(true);
		return true;
	}
	return false;
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
void ASoldierPawn::ToGroupForward()
{
	SetActorRotation(mGroup->GetGroupForward().Rotation());
}
FVector ASoldierPawn::GetSpawnProjectileLoction()
{

	return GetActorLocation();
}
ASoldierPawn * ASoldierPawn::GetBestEnemy(const TArray<ASoldierPawn *> & SeachList)
{
	if (SeachList.Num() > 0)
	{
		FVector SoldierPosition = GetOriginGroundTile()->GetActorLocation();
		ASoldierPawn * TemSoldier = nullptr;
		for (auto IterSoldier : SeachList)
		{
			if (TemSoldier == nullptr)
			{
				TemSoldier = IterSoldier;
				continue;
			}
			FVector IterSoldierLocation = IterSoldier->GetOriginGroundTile()->GetActorLocation();
			FVector TemSoldierLocation = TemSoldier->GetOriginGroundTile()->GetActorLocation();
			if (FVector::DistSquared(IterSoldierLocation, SoldierPosition) < FVector::DistSquared(TemSoldierLocation, SoldierPosition))
			{
				TemSoldier = IterSoldier;
			}
		}
		return TemSoldier;
	}
	return nullptr;
}
void ASoldierPawn::SetGenericTeamId(const FGenericTeamId& NewTeamID)
{
	if (TeamID != NewTeamID)
	{
		TeamID = NewTeamID;
	}
}
void ASoldierPawn::SetOriginGroundTile(class AGroundTileActor * InTile)
{
	OriginGroundTile = InTile;
}
void ASoldierPawn::SetTargetGroundTile(class AGroundTileActor * InTile)
{
	TargetGroundTile = InTile;
}
void ASoldierPawn::MoveToTargetEnd()
{
	if (SoldierData->IsUserData())
	{
		int32 VisibleDis = SoldierData->GetVisibleRange();
		TArray<AGroundTileActor*>  AroundTiles;
		if (OriginGroundTile)
		{
			GameManager::GetGroundTileAroundSoldier(OriginGroundTile, VisibleDis, AroundTiles,true);
			AroundTiles.Add(OriginGroundTile);
			for (auto IterTile : AroundTiles)
			{
				IterTile->DecreaseVisibilityCounter();
			}
		}

		AroundTiles.Empty();
		if (TargetGroundTile)
		{
			GameManager::GetGroundTileAroundSoldier(TargetGroundTile, VisibleDis, AroundTiles,true);
			AroundTiles.Add(TargetGroundTile);
			for (auto IterTile : AroundTiles)
			{
				IterTile->IncreaseVisibilityCounter();
			}
		}
	}
	if (TargetGroundTile)
	{
		OriginGroundTile->RemoveSoldier(this);
		TargetGroundTile->AddSoldier(this);
		OriginGroundTile->SetBusy(false);
		TargetGroundTile->SetBusy(false);
		OriginGroundTile = TargetGroundTile;
		TargetGroundTile = nullptr;
	}
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