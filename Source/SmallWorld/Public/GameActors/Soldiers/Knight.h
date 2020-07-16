#pragma once
#include "SoldierPawn.h"
#include "Knight.generated.h"



UCLASS()
class AKnight : public ASoldierPawn
{
	GENERATED_BODY()

public:
	AKnight();
	~AKnight();
	// --------  Overirde GameObjectClass -------------
	virtual void  On_Start() override;
	// -------- Override EnableAttackPawnClass ---------
	


	USoldierInstantWeapon * InstantWeaponClass;


	UPROPERTY(EditAnywhere)
		FInstantWeaponInfo	InstantWeaponInfo;

};