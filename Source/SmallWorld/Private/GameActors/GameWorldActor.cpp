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
	float Extent = TileGameConfig::TileMapSize * TileGameConfig::TileSize * 0.5;

	CollisionBox->SetBoxExtent(FVector(Extent, Extent, Extent));

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