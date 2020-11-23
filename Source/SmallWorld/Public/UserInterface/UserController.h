#pragma once
#include "GameController.h"
#include "EditLandscapeHandle.h"


#include "UserController.generated.h"

class ASoldierPawn;

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
	static AUserController * GetInstance();

	virtual void On_Init() override;
	virtual void On_Start() override;
	virtual void On_Tick(float delta) override;
	virtual void On_Delete() override;

	void		 ChangeControllType(EControllType ControllType);

	class AActor * TrySelectGameActor(FVector2D ScreenPosition);


	bool	HavePriviewActor();
	void	UpdatePriviewActor(FVector2D ScreenPosition, FString IconName = TEXT(""));
	void	DropPriviewActor();
	void	DestroyPriviewActor();

protected:
	ASoldierPawn * CurrentSelectedSoldier;
	class APreviewActor *  PreviewActor;

	EControllType		CurrentControllType;
	ALandscape *		CurrentLandscape;
	ULandscapeInfo *	CurrentLandscapeInfo;

	void LandscapePaint(ALandscape * Landscape, ULandscapeInfo * LandscapeInfo, FVector Location, float Radius, float Falloff);
private:
	static AUserController * Instance;
};

#define User_Controller AUserController::GetInstance()