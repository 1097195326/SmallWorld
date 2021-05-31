#include "WrapActor.h"

AWrapActor::AWrapActor()
{

}
void AWrapActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	On_Init();
}
void AWrapActor::BeginPlay()
{
	Super::BeginPlay();
	On_Start();
}
void AWrapActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	On_Tick(DeltaSeconds);
}
void AWrapActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	On_End();
	Super::EndPlay(EndPlayReason);
}
void AWrapActor::BeginDestroy()
{
	On_Delete();
	Super::BeginDestroy();
}