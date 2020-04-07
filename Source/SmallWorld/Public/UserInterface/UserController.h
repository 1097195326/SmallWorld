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
	static AUserController * Instance;

	virtual void On_Init() override;
	virtual void On_Start() override;
	virtual void On_Tick(float delta) override;
	virtual void On_Delete() override;

	void		 ChangeControllType(EControllType ControllType);

	class AGameActor * TrySelectGameActor(FVector2D ScreenPosition);

	bool	HavePriviewActor();
	void	UpdatePriviewActor(FVector2D ScreenPosition, FString IconName = TEXT(""));
	void	DropPriviewActor();
	void	DestroyPriviewActor();
protected:
	class APreviewActor *  PreviewActor;

	EControllType		CurrentControllType;
	ALandscape *		CurrentLandscape;
	ULandscapeInfo *	CurrentLandscapeInfo;

	void LandscapePaint(ALandscape * Landscape, ULandscapeInfo * LandscapeInfo, FVector Location, float Radius, float Falloff);

};

