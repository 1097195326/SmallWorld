#pragma once
#include "GameController.h"
#include "EditLandscapeHandle.h"


#include "UserController.generated.h"

UCLASS()
class AUserController : public AGameController
{
	GENERATED_BODY()

public:
	enum  EControllType
	{
		ECT_None,
		ECT_ShowSomething,
		ECT_InputSomething,

	};
	virtual void On_Init() override;
	virtual void On_Start() override;
	virtual void On_Tick(float delta) override;
	virtual void On_Delete() override;

	virtual bool InputKey(FKey Key, EInputEvent EventType, float AmountDepressed, bool bGamepad) override;
	virtual bool InputTouch(uint32 Handle, ETouchType::Type Type, const FVector2D& TouchLocation, float Force, FDateTime DeviceTimestamp, uint32 TouchpadIndex) override;
	virtual bool InputAxis(FKey Key, float Delta, float DeltaTime, int32 NumSamples, bool bGamepad) override;

	void		 ChangeControllType(EControllType ControllType);
protected:
	EControllType		CurrentControllType;
	ALandscape *		CurrentLandscape;
	ULandscapeInfo *	CurrentLandscapeInfo;

	void LandscapePaint(ALandscape * Landscape, ULandscapeInfo * LandscapeInfo, FVector Location, float Radius, float Falloff);

};

