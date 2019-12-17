#include "GameActor.h"

AGameActor::AGameActor()
{

}
void AGameActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	On_Init();
}
void AGameActor::BeginDestroy()
{
	On_Delete();
	Super::BeginDestroy();
}
void AGameActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	On_Tick(DeltaSeconds);
}
void AGameActor::On_Init()
{

}
void AGameActor::On_Tick(float delta)
{

}
void AGameActor::On_Delete()
{

}