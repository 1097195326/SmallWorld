#include "GameWorldActor.h"
#include "GameConfig.h"

AGameWorldActor::AGameWorldActor()
{
	RootComponent = CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetHiddenInGame(false);
	CollisionBox->ShapeColor = FColor(0, 0, 255, 255);

}
void AGameWorldActor::On_Init()
{
	

}
void AGameWorldActor::On_Tick(float DeltaSeconds)
{

}
void AGameWorldActor::On_Delete()
{

}
TSharedPtr<SWidget>	AGameWorldActor::CreateActorDetailWidget()
{
	return SNullWidget::NullWidget;
}