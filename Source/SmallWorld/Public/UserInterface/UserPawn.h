#pragma once
#include "WrapPawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "UserPawn.generated.h"

UCLASS()
class AUserPawn : public AWrapPawn
{
	GENERATED_BODY()
private:
	static AUserPawn * Instance;
public:
	AUserPawn(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	static AUserPawn * GetInstance();

	virtual void On_Init() override;
	virtual void On_Start() override;
	virtual void On_Tick(float delta) override;
	virtual void On_Delete() override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual UPawnMovementComponent* GetMovementComponent() const override;

private:
	void InitializeDefaultPawnInputBindings();
	void MoveLeftAndRight(float dle);
	void MoveUpAndDown(float dle);
		 
	void TouchPress(ETouchIndex::Type touchIndex, FVector location);
	void TouchMove(ETouchIndex::Type touchIndex, FVector location);
	void TouchRelease(ETouchIndex::Type touchIndex, FVector location);
		 
	void GetPressedFinger(int &num);
private:
	class AUserController * mController;
	
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent * armComponent;
	UPROPERTY(VisibleAnywhere)
	UCameraComponent * cameraComponent;
	UPROPERTY(VisibleAnywhere)
	UFloatingPawnMovement * PawnMovement;

	UFUNCTION(BlueprintCallable, Category = "Pawn")
		virtual void MoveForward(float Val);
	UFUNCTION(BlueprintCallable, Category = "Pawn")
		virtual void MoveRight(float Val);
	UFUNCTION(BlueprintCallable, Category = "Pawn")
		virtual void MoveUp_World(float Val);
	UFUNCTION(BlueprintCallable, Category = "Pawn")
		virtual void TurnAtRate(float Rate);
	UFUNCTION(BlueprintCallable, Category = "Pawn")
		virtual void LookUpAtRate(float Rate);

	void LeftMouseButtonOnPressed();
	void RightMouseButtonOnReleased();
};

#define  User_Pawn AUserPawn::GetInstance()