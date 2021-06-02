#include "UserPawn.h"
#include "UserController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerInput.h"

// test exec
#include "SoldierPawnController.h"
#include "SoldierPawn.h"
#include "SoldierGroup.h"
#include "RectFormation.h"
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
#include "GroupFightState.h"

AUserPawn * AUserPawn::Instance = nullptr;
AUserPawn * AUserPawn::GetInstance()
{
	return Instance;
}
AUserPawn::AUserPawn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Instance = this;

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

void AUserPawn::InitializeDefaultPawnInputBindings()
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

		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping("LeftMouse",EKeys::LeftMouseButton));
		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping("RightMouse",EKeys::RightMouseButton));

		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping("Touch1", EKeys::TouchKeys[0]));
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

	PlayerInputComponent->BindAction("LeftMouse", IE_Pressed, this, &AUserPawn::LeftMouseButtonOnPressed);
	PlayerInputComponent->BindAction("RightMouse", IE_Released, this, &AUserPawn::RightMouseButtonOnReleased);


}

void AUserPawn::LeftMouseButtonOnPressed()
{
	APlayerController * PlayerController = Cast<APlayerController>(Controller);
	/*if (PlayerController)
	{
		FHitResult HitResult;
		PlayerController->GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_WorldStatic), false, HitResult);
		ALandscape * Landscape = Cast<ALandscape>(HitResult.GetActor());
		if (Landscape)
		{
			ULandscapeInfo * LandscapeInfo = Landscape->CreateLandscapeInfo();
			ULandscapeLayerInfoObject * LayerInfo = LandscapeInfo->GetLayerInfoByName("auto");
			
			FCLandscapeToolTarget  ToolTarget;
			ToolTarget.LandscapeInfo = LandscapeInfo;
			ToolTarget.LayerInfo = LayerInfo;
			ToolTarget.TargetType = ECLandscapeToolTargetType::Weightmap;

			FVector LandscapePos = Landscape->LandscapeActorToWorld().InverseTransformPosition(HitResult.Location);

			TArray<FCLandscapeToolInteractorPosition> InteractorPositions;
			InteractorPositions.Empty(1);
			InteractorPositions.Emplace(FVector2D(LandscapePos),false);

			FCLandscapeBrushCircle_Smooth * Brush = new FCLandscapeBrushCircle_Smooth(LandscapeInfo, 500.f, 0.5f);
			FCLandscapeToolStrokePaint * StrokePaint = new FCLandscapeToolStrokePaint(ToolTarget);

			StrokePaint->Apply(Brush, InteractorPositions);


		}
	}*/
}
void AUserPawn::RightMouseButtonOnReleased()
{

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
static int RedIndex = 0;

void AUserPawn::Prepare()
{
	TArray<AActor*> Points;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), Points);

	FVector RedLocation = Points[0]->GetActorLocation();
	FVector BlueLocation = Points[1]->GetActorLocation();

	RedGroupManager = new SoldierGroupManager();
	BlueGroupManager = new SoldierGroupManager();

	RedGroupManager->SetOriginAndForward(RedLocation, (BlueLocation - RedLocation).GetSafeNormal());
	BlueGroupManager->SetOriginAndForward(BlueLocation, (RedLocation - BlueLocation).GetSafeNormal());
	
	FTransform  RedTran(RedLocation);
	FTransform  BlueTran(BlueLocation);

	RedIndex = 0;
	GetWorld()->GetTimerManager().SetTimer(hendle, this, &AUserPawn::SpawnSoldier, 1.f, true);

}
void AUserPawn::SpawnSoldier()
{
	TArray<AActor*> Points;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), Points);

	FVector RedLocation = Points[0]->GetActorLocation();
	FVector BlueLocation = Points[1]->GetActorLocation();
	
	RedLocation.Z = 0.f;
	BlueLocation.Z = 150.f;

	FTransform  RedTran(RedLocation);
	FTransform  BlueTran(BlueLocation);

	static int TeamIndex = 1;


	while(RedIndex < 1/*KnightGroupMaxNum*/)
	{
		RedIndex++;

		UClass * soldierClass = LoadClass<ASoldierPawn>(this, TEXT("/Game/Soldiers/Knight_BP.Knight_BP_C"));
		ASoldierPawn * RedSoldierPawn = Cast<ASoldierPawn>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this, soldierClass, RedTran, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn));
		if (RedSoldierPawn)
		{
			RedSoldierPawn->SetGenericTeamId(FGenericTeamId(TeamIndex++));

			RedGroupManager->PushSoldierToGroup(RedSoldierPawn);

			UGameplayStatics::FinishSpawningActor(RedSoldierPawn, RedTran);
		}
		ASoldierPawn * BlueSoldierPawn = Cast<ASoldierPawn>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this, soldierClass, RedTran, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn));
		if (BlueSoldierPawn)
		{
			BlueSoldierPawn->SetGenericTeamId(FGenericTeamId(TeamIndex++));

			BlueGroupManager->PushSoldierToGroup(BlueSoldierPawn);

			UGameplayStatics::FinishSpawningActor(BlueSoldierPawn, BlueTran);
		}
		/*RedSoldierPawn->SetEnemy(BlueSoldierPawn);
		BlueSoldierPawn->SetEnemy(RedSoldierPawn);
		Cast<AAIController>(RedSoldierPawn->GetController())->MoveToActor(BlueSoldierPawn);
		Cast<AAIController>(BlueSoldierPawn->GetController())->MoveToActor(RedSoldierPawn);*/
		return;
	}
	GetWorld()->GetTimerManager().ClearTimer(hendle);
}
void AUserPawn::Attack()
{
	BlueGroupManager->GetCurrentGroup()->ChangeGrouyStateByIndex(I_AutoFightIndex);
	RedGroupManager->GetCurrentGroup()->ChangeGrouyStateByIndex(I_AutoFightIndex);
	/*TArray<AActor*> Points;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASoldierPawn::StaticClass(), Points);
	for (int i = 0; i< Points.Num() ;i ++)
	{
		Points[i]->Destroy();
	}
	GEngine->ForceGarbageCollection(true);*/
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
	group->ChangeFormationByIndex(SquareRectFormationType);

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