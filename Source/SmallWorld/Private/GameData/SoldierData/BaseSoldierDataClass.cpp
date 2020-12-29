#include "BaseSoldierDataClass.h"
#include "GameDataManager.h"
#include "CommandCenterDataClass.h"
#include "HordeDataClass.h"
#include "GroundTileActor.h"



BaseSoldierDataClass::BaseSoldierDataClass()
{
	SoldierType = Soldier_None;
	SoldierPawn = nullptr;
	CommandCenter = nullptr;
	CurrentLevel = 0;
	CurrentHealth = 100.f;

}
BaseSoldierDataClass::~BaseSoldierDataClass()
{
	if (SoldierPawn)
	{
		SoldierPawn->BeginDestroy();
		SoldierPawn = nullptr;
	}

}
void BaseSoldierDataClass::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	Writer->WriteObjectStart("BaseSoldierDataClass");
	RuntimeDataClass::Serialization(Writer);

	if (CommandCenter)
	{
		Writer->WriteValue("ArmyCenterID", CommandCenter->GetObjectId().ToString());
	}
	if (SoldierPawn)
	{
		Writer->WriteValue("SoldierLocation", SoldierPawn->GetOriginGroundTile()->GetActorLocation().ToString());
		Writer->WriteValue("SoldierRotation", SoldierPawn->GetActorRotation().ToString());
	}
	Writer->WriteValue("SoldierName", *SoldierName);
	Writer->WriteValue("CurrentHealth", CurrentHealth);
	Writer->WriteValue("CurrentLevel", CurrentLevel);

	Writer->WriteObjectEnd();
}
void BaseSoldierDataClass::Deserialization(TSharedPtr<FJsonObject> JsonObject)
{
	RuntimeDataClass::Deserialization(JsonObject->GetObjectField("RuntimeDataClass"));

	SoldierName = JsonObject->GetStringField("SoldierName");
	CurrentHealth = JsonObject->GetNumberField("CurrentHealth");
	CurrentLevel = JsonObject->GetIntegerField("CurrentLevel");

	FString ArmyCenterID;
	if (JsonObject->TryGetStringField("ArmyCenterID", ArmyCenterID))
	{
		FGuid::Parse(ArmyCenterID, CommandCenterId);
	}
	FString SoldierLocation, SoldierRotation;
	JsonObject->TryGetStringField("SoldierLocation", SoldierLocation);
	JsonObject->TryGetStringField("SoldierRotation", SoldierRotation);
	
	//------
	SetSoldierConfigByName(SoldierName);

	FVector TemLocation; TemLocation.InitFromString(SoldierLocation);
	FRotator TemRotator; TemRotator.InitFromString(SoldierRotation);
	ASoldierPawn * TemSoldier = SpawnSoldierActor(SoldierName);
	TemSoldier->SetActorTransform(FTransform(TemRotator, TemLocation));

}
ASoldierPawn * BaseSoldierDataClass::SpawnSoldierActor(const FString & InSoldierName)
{
	FString ClassPath = FString::Printf(TEXT("/Game/Blueprint/%s_BP.%s_BP_C"), *InSoldierName, *InSoldierName);
	UClass * SoldierClass = LoadClass<ASoldierPawn>(nullptr, *ClassPath);
	//ASoldierPawn* TemSoldier = User_GameInstance->GetWorld()->SpawnActor<ASoldierPawn>(SoldierClass);

	FActorSpawnParameters Paramerter;
	Paramerter.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	ASoldierPawn* TemSoldier = User_GameInstance->GetWorld()->SpawnActor<ASoldierPawn>(SoldierClass, Paramerter);
	TemSoldier->SetSoldierData(this);
	return TemSoldier;
}
void BaseSoldierDataClass::DestroySoldier()
{
	if (SoldierPawn)
	{
		SoldierPawn->Destroy();
		SoldierPawn = nullptr;
	}
}
void BaseSoldierDataClass::SetCommandCenter(class CommandCenterDataClass * InCommandCenter)
{
	CommandCenter = InCommandCenter;
}
CommandCenterDataClass * BaseSoldierDataClass::GetCommandCenter()
{
	return CommandCenter;
}
bool BaseSoldierDataClass::IsUserData()
{
	HordeDataClass * HordeData = CommandCenter->GetHordeBelongTo();
	return GameDataManager::GetInstance()->IsUserHordeData(HordeData);
}
void BaseSoldierDataClass::SetSoldierConfigByName(FString InName)
{
	SoldierName = InName;
	SoldierConfig = GameDataManager::GetInstance()->GetGameConfigData()->GetSoldierConfig(InName);
}
void BaseSoldierDataClass::SetCurrentMovability(float InValue)
{
	CurrentMovability = InValue;
	if (CurrentMovability > GetLevelInfo().Movability)
	{
		CurrentMovability = GetLevelInfo().Movability;
	}
}
void BaseSoldierDataClass::SetCurrentHealth(float InValue)
{
	CurrentHealth = InValue;
	if (CurrentHealth > GetLevelInfo().Health)
	{
		CurrentHealth = GetLevelInfo().Health;
	}
}
void BaseSoldierDataClass::ReturnMovability(float InTime)
{
	CurrentReturnMovabilityInterval += InTime;
	if (CurrentReturnMovabilityInterval > GetLevelInfo().MovabilityReturnInterval)
	{
		CurrentReturnMovabilityInterval -= GetLevelInfo().MovabilityReturnInterval;
		SetCurrentMovability(CurrentMovability + GetLevelInfo().MovabilityReturnSpeed);
	}
}
void BaseSoldierDataClass::ReturnHealth(float InTime)
{
	CurrentReturnHealthInterval += InTime;
	if (CurrentReturnHealthInterval > GetLevelInfo().HealthReturnInterval)
	{
		CurrentReturnHealthInterval -= GetLevelInfo().HealthReturnInterval;
		SetCurrentHealth(CurrentHealth + GetLevelInfo().HealthReturnSpeed);
	}
}
void BaseSoldierDataClass::ReturnAttackPower(float InTime)
{
	CurrentAttackInterval += InTime;
	if (CurrentAttackInterval > SoldierConfig.AttackInterval)
	{
		CurrentAttackInterval = SoldierConfig.AttackInterval;
	}
}