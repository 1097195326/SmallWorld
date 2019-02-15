#pragma once
#include "GamePawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "UserPawn.generated.h"

UCLASS()
class AUserPawn : public AGamePawn
{
	GENERATED_BODY()
public:
	//AUserPawn();
	AUserPawn(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void On_Init() override;
	virtual void On_Start() override;
	virtual void On_Tick(float delta) override;
	virtual void On_Delete() override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual UPawnMovementComponent* GetMovementComponent() const override;

private:
	void	MoveLeftAndRight(float dle);
	void	MoveUpAndDown(float dle);

	void	TouchPress(ETouchIndex::Type touchIndex, FVector location);
	void	TouchMove(ETouchIndex::Type touchIndex, FVector location);
	void	TouchRelease(ETouchIndex::Type touchIndex, FVector location);

	void	GetPressedFinger(int &num);
private:
	class	AUserController * mController;
	
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent *	armComponent;
	UPROPERTY(VisibleAnywhere)
	UCameraComponent *		cameraComponent;
	UPROPERTY(VisibleAnywhere)
		UFloatingPawnMovement * PawnMovement;

};

