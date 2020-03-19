#include "CityActor.h"


ACityActor::ACityActor()
{
	
	//mGeneralGoal = new GeneralGoal();
	//mGeneralGoal->InitWithCityActor(this);

	RootComponent = CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetHiddenInGame(false);
	CollisionBox->ShapeColor = FColor(0,255,0,255);

	BaseMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CityMeshComponent"));
	BaseMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	BaseMeshComponent->SetRelativeScale3D(FVector(0.1f));

}
void ACityActor::On_Init()
{

}
void ACityActor::On_GameUpdate()
{
	
	//if (mGeneralGoal)
	//{
	//	//mGeneralGoal->Process();
	//}
	for (auto groupManager : mGroupManagers)
	{
		groupManager->On_GameUpdate();
	}

}
void ACityActor::On_Delete()
{
	//mGeneralGoal->End();

	/*delete mGeneralGoal;
	mGeneralGoal = nullptr;*/
}