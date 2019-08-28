#include "GameCharacter.h"




void AGameCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	On_Init();
}
void AGameCharacter::BeginPlay()
{
	Super::BeginPlay();

	On_Start();
}
void AGameCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	On_Tick(DeltaSeconds);
}
void AGameCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	On_End();

	Super::EndPlay(EndPlayReason);
}
void AGameCharacter::BeginDestroy()
{
	On_Delete();

	Super::BeginDestroy();
}