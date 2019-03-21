#include "UserPawn.h"
#include "UserController.h"
#include "Kismet/GameplayStatics.h"

// test exec
#include "SoldierPawnController.h"
#include "SoldierPawn.h"
#include "BaseGroup.h"
#include "HorizonalRectFormation.h"
#include "ConeFormation.h"
#include "CircleFormation.h"
#include "Engine/TargetPoint.h"
#include "Projectile.h"


AUserPawn::AUserPawn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	PawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("PawnMovement"));
	PawnMovement->SetUpdatedComponent(RootComponent);

	armComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("ArmComponent"));
	armComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	armComponent->bAbsoluteRotation = true;
	armComponent->TargetArmLength = 800.f;
	armComponent->bEnableCameraLag = true;
	armComponent->CameraLagSpeed = 6.f;
	armComponent->RelativeRotation = FRotator(-60.f, 0.f, 0.f);
	armComponent->bDoCollisionTest = false;

	cameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	cameraComponent->SetupAttachment(armComponent, USpringArmComponent::SocketName);
	cameraComponent->bUsePawnControlRotation = false;

}
void AUserPawn::On_Init()
{
	mController = (AUserController*)Controller;

}
void AUserPawn::On_Start()
{

}
void AUserPawn::On_Tick(float delta)
{

}
void AUserPawn::On_Delete()
{

}
void AUserPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

#if PLATFORM_IOS || PLATFORM_ANDROID
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AUserPawn::TouchPress);
	PlayerInputComponent->BindTouch(IE_Repeat, this, &AUserPawn::TouchMove);
	PlayerInputComponent->BindTouch(IE_Released, this, &AUserPawn::TouchRelease);
#else
	PlayerInputComponent->BindAxis(TEXT("MoveLeftAndRight"), this, &AUserPawn::MoveLeftAndRight);
	PlayerInputComponent->BindAxis(TEXT("MoveUpAndDown"), this, &AUserPawn::MoveUpAndDown);
#endif
	


}
UPawnMovementComponent * AUserPawn::GetMovementComponent() const
{
	return PawnMovement;
}
void AUserPawn::TouchPress(ETouchIndex::Type touchIndex, FVector location)
{

}
void AUserPawn::TouchMove(ETouchIndex::Type touchIndex, FVector location)
{

}
void AUserPawn::TouchRelease(ETouchIndex::Type touchIndex, FVector location)
{

}
void AUserPawn::GetPressedFinger(int &num)
{
	FVector2D oneLoc,twoLoc;
	bool  oneP,twoP;
	mController->GetInputTouchState(ETouchIndex::Touch1, oneLoc.X, oneLoc.Y, oneP);
	mController->GetInputTouchState(ETouchIndex::Touch2, twoLoc.X, twoLoc.Y, twoP);
	if (oneP && twoP)
	{
		num = 2;
	}else if (oneP || twoP)
	{
		num = 1;
	}else
	{
		num = 0;
	}
}

void AUserPawn::MoveLeftAndRight(float dle)
{
	AddMovementInput(GetActorRightVector(), dle);
}
void AUserPawn::MoveUpAndDown(float dle)
{
	AddMovementInput(GetActorForwardVector(), dle);
}
void AUserPawn::CreateGroup()
{
	TArray<AActor*> soldiers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASoldierPawn::StaticClass(), soldiers);
	BaseGroup * group = new BaseGroup();

	for (int i = 0; i < soldiers.Num(); i++)
	{
		ASoldierPawn * Soldier = Cast<ASoldierPawn>(soldiers[i]);
		group->AddSoldierToGroup(Soldier);
	}
	group->ChangeFormation(new HorizonalRectFormation());
	
	for (int i = 0; i < soldiers.Num(); i++)
	{
		ASoldierPawn * Soldier = Cast<ASoldierPawn>(soldiers[i]);
		ASoldierPawnController * SoldierController = Cast<ASoldierPawnController>(Soldier->GetController());
		SoldierController->SetMoveToLocation(Soldier->mFormationPosition);
	}
}
void AUserPawn::Fire()
{

	TArray<AActor*> Points;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), Points);

	FVector FireLocation = Points[0]->GetActorLocation();
	FVector TargetLocation = Points[1]->GetActorLocation();

	FTransform transform(FireLocation);
	UClass * ProjectileClass = LoadClass<AActor>(this, TEXT("/Game/Projectile/Projectile_BP.Projectile_BP_C"));
	 
	AProjectile * projectile =Cast<AProjectile>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this, ProjectileClass, transform));
	if (projectile != nullptr)
	{
		float Gravity = projectile->MoveComponent->GetGravityZ();

		FVector2D HorizontalDistance = FVector2D(TargetLocation.X - FireLocation.X, TargetLocation.Y - FireLocation.Y);
		FVector2D HorizontalVelocity = FVector2D(TargetLocation.X - FireLocation.X, TargetLocation.Y - FireLocation.Y).GetSafeNormal() * 500;
		float AllTime = HorizontalDistance.Size() / 500.f;
		float VelocityZ = - (Gravity * AllTime * AllTime * 0.5f - TargetLocation.Z + FireLocation.Z)/AllTime;
		projectile->SetVelocity(FVector(HorizontalVelocity.X, HorizontalVelocity.Y, VelocityZ));

		UGameplayStatics::FinishSpawningActor(projectile, transform);
	}


}