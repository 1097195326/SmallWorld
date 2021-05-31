#include "WrapCharacter.h"




void AWrapCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	On_Init();
}
void AWrapCharacter::BeginPlay()
{
	Super::BeginPlay();
	On_Start();
}
void AWrapCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	On_Tick(DeltaSeconds);
}
void AWrapCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	On_End();
	Super::EndPlay(EndPlayReason);
}
void AWrapCharacter::BeginDestroy()
{
	On_Delete();
	Super::BeginDestroy();
}