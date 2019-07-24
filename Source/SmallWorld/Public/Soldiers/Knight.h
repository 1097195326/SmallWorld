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
	// --------  Overirde GObject -------------
	virtual void  On_Start() override;



	USoldierInstantWeapon * InstantWeapon;


	UPROPERTY(EditAnywhere)
		FInstantWeaponInfo	InstantWeaponInfo;

};