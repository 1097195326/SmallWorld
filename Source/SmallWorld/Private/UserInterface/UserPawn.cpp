#include "UserPawn.h"
#include "UserController.h"

#include "Components/CapsuleComponent.h"

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