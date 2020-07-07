#include "GameActor.h"

AGameActor::AGameActor()
{

}
void AGameActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	On_Init();
}
void AGameActor::BeginPlay()
{
	Super::BeginPlay();
	On_Start();
}
void AGameActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	On_Tick(DeltaSeconds);
}
void AGameActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	On_End();
	Super::EndPlay(EndPlayReason);
}
void AGameActor::BeginDestroy()
{
	On_Delete();
	Super::BeginDestroy();
}