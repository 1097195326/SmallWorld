#include "UserPawn.h"
#include "UserController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerInput.h"

// test exec
#include "SoldierPawnController.h"
#include "SoldierPawn.h"
#include "SoldierGroup.h"
#include "HorizonalRectFormation.h"
#include "ConeFormation.h"
#include "CircleFormation.h"
#include "Engine/TargetPoint.h"
#include "Projectile.h"
#include "SoldierGroupManager.h"
// test soldier
#include "Archer.h"
#include "Footman.h"
#include "Griffin.h"
#include "Horseman.h"
#include "Knight.h"
#include "Mage.h"
#include "SiegeEngine.h"


AUserPawn::AUserPawn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	PawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("PawnMovement"));
	PawnMovement->SetUpdatedComponent(RootComponent);
/*
	armComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("ArmComponent"));
	armComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	armComponent->bAbsoluteRotation = true;
	armComponent->TargetArmLength = 1500.f;
	armComponent->bEnableCameraLag = true;
	armComponent->CameraLagSpeed = 6.f;
	armComponent->RelativeRotation = FRotator(-60.f, 0.f, 0.f);
	armComponent->bDoCollisionTest = false;

	cameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	cameraComponent->SetupAttachment(armComponent, USpringArmComponent::SocketName);
	cameraComponent->bUsePawnControlRotation = false;*/

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

void InitializeDefaultPawnInputBindings()
{
	static bool bBindingsAdded = false;
	if (!bBindingsAdded)
	{
		bBindingsAdded = true;

		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("DefaultPawn_MoveForward", EKeys::W, 1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("DefaultPawn_MoveForward", EKeys::S, -1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("DefaultPawn_MoveForward", EKeys::Up, 1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("DefaultPawn_MoveForward", EKeys::Down, -1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("DefaultPawn_MoveForward", EKeys::Gamepad_LeftY, 1.f));

		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("DefaultPawn_MoveRight", EKeys::A, -1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("DefaultPawn_MoveRight", EKeys::D, 1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("DefaultPawn_MoveRight", EKeys::Gamepad_LeftX, 1.f));

		// HACK: Android controller bindings in ini files seem to not work
		//  Direct overrides here some to work
#if !PLATFORM_ANDROID
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("DefaultPawn_MoveUp", EKeys::Gamepad_LeftThumbstick, 1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("DefaultPawn_MoveUp", EKeys::Gamepad_RightThumbstick, -1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("DefaultPawn_MoveUp", EKeys::Gamepad_FaceButton_Bottom, 1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("DefaultPawn_MoveUp", EKeys::LeftControl, -1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("DefaultPawn_MoveUp", EKeys::SpaceBar, 1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("DefaultPawn_MoveUp", EKeys::C, -1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("DefaultPawn_MoveUp", EKeys::E, 1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("DefaultPawn_MoveUp", EKeys::Q, -1.f));
#else
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("DefaultPawn_MoveUp", EKeys::Gamepad_LeftTriggerAxis, -0.5f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("DefaultPawn_MoveUp", EKeys::Gamepad_RightTriggerAxis, 0.5f));
#endif

		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("DefaultPawn_TurnRate", EKeys::Gamepad_RightX, 1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("DefaultPawn_TurnRate", EKeys::Left, -1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("DefaultPawn_TurnRate", EKeys::Right, 1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("DefaultPawn_Turn", EKeys::MouseX, 1.f));

		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("DefaultPawn_LookUpRate", EKeys::Gamepad_RightY, 1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("DefaultPawn_LookUp", EKeys::MouseY, -1.f));
}
}

void AUserPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

		InitializeDefaultPawnInputBindings();

		PlayerInputComponent->BindAxis("DefaultPawn_MoveForward", this, &AUserPawn::MoveForward);
		PlayerInputComponent->BindAxis("DefaultPawn_MoveRight", this, &AUserPawn::MoveRight);
		PlayerInputComponent->BindAxis("DefaultPawn_MoveUp", this, &AUserPawn::MoveUp_World);
		PlayerInputComponent->BindAxis("DefaultPawn_Turn", this, &AUserPawn::AddControllerYawInput);
		PlayerInputComponent->BindAxis("DefaultPawn_TurnRate", this, &AUserPawn::TurnAtRate);
		PlayerInputComponent->BindAxis("DefaultPawn_LookUp", this, &AUserPawn::AddControllerPitchInput);
		PlayerInputComponent->BindAxis("DefaultPawn_LookUpRate", this, &AUserPawn::LookUpAtRate);
	
}
float BaseTurnRate = 45.f;
float BaseLookUpRate = 45.f;
float BaseMoveRate = 2.f;

void AUserPawn::MoveRight(float Val)
{
	if (Val != 0.f)
	{
		if (Controller)
		{
			FRotator const ControlSpaceRot = Controller->GetControlRotation();

			// transform to world space and add it
			AddMovementInput(FRotationMatrix(ControlSpaceRot).GetScaledAxis(EAxis::Y), Val * BaseMoveRate);
		}
	}
}

void AUserPawn::MoveForward(float Val)
{
	if (Val != 0.f)
	{
		if (Controller)
		{
			FRotator const ControlSpaceRot = Controller->GetControlRotation();

			// transform to world space and add it
			AddMovementInput(FRotationMatrix(ControlSpaceRot).GetScaledAxis(EAxis::X), Val * BaseMoveRate);
		}
	}
}

void AUserPawn::MoveUp_World(float Val)
{
	if (Val != 0.f)
	{
		AddMovementInput(FVector::UpVector, Val * BaseMoveRate);
	}
}

void AUserPawn::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds() * 1);
}

void AUserPawn::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds() * 1);
}

//void AUserPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
//	Super::SetupPlayerInputComponent(PlayerInputComponent);
//
//#if PLATFORM_IOS || PLATFORM_ANDROID
//	PlayerInputComponent->BindTouch(IE_Pressed, this, &AUserPawn::TouchPress);
//	PlayerInputComponent->BindTouch(IE_Repeat, this, &AUserPawn::TouchMove);
//	PlayerInputComponent->BindTouch(IE_Released, this, &AUserPawn::TouchRelease);
//#else
//	PlayerInputComponent->BindAxis(TEXT("MoveLeftAndRight"), this, &AUserPawn::MoveLeftAndRight);
//	PlayerInputComponent->BindAxis(TEXT("MoveUpAndDown"), this, &AUserPawn::MoveUpAndDown);
//#endif
//	
//
//
//}
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
void AUserPawn::Prepare()
{
	TArray<AActor*> Points;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), Points);

	FVector RedLocation = Points[0]->GetActorLocation();
	FVector BlueLocation = Points[1]->GetActorLocation();

	RedGroupMange = new SoldierGroupManager();
	BlueGroupMange = new SoldierGroupManager();

	FTransform  RedTran(RedLocation);
	FTransform  BlueTran(BlueLocation);

	for (int i = 0; i < 1; i++)
	{
		UClass * soldierClass = LoadClass<ASoldierPawn>(this, TEXT("/Game/Soldiers/Knight.Knight_C"));
		ASoldierPawn * soldierPawn = Cast<ASoldierPawn>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this, soldierClass, RedTran));
		if (soldierPawn)
		{
			UGameplayStatics::FinishSpawningActor(soldierPawn, RedTran);
			RedGroupMange->PushSoldierToGroup(soldierPawn);
		}
	}
	for (int i = 0; i < 1; i++)
	{
		UClass * soldierClass = LoadClass<ASoldierPawn>(this, TEXT("/Game/Soldiers/Knight.Knight_C"));
		ASoldierPawn * soldierPawn = Cast<ASoldierPawn>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this, soldierClass, RedTran));
		if (soldierPawn)
		{
			UGameplayStatics::FinishSpawningActor(soldierPawn, BlueTran);
			BlueGroupMange->PushSoldierToGroup(soldierPawn);
		}
	}



}
void AUserPawn::Attack()
{

}
void AUserPawn::CreateGroup()
{
	TArray<AActor*> soldiers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASoldierPawn::StaticClass(), soldiers);
	SoldierGroup * group = new SoldierGroup();

	for (int i = 0; i < soldiers.Num(); i++)
	{
		ASoldierPawn * Soldier = Cast<ASoldierPawn>(soldiers[i]);
		group->AddSoldierToGroup(Soldier);
	}
	group->ChangeFormation(new HorizonalRectFormation());
	
	for (int i = 0; i < soldiers.Num(); i++)
	{
		ASoldierPawn * Soldier = Cast<ASoldierPawn>(soldiers[i]);
		Soldier->SetMoveToLocation(Soldier->mFormationPosition);
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