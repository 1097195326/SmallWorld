#include "GroundTileActor.h"
#include "Kismet/KismetSystemLibrary.h"
#include "CastleTileActor.h"
#include "SoldierPawn.h"
#include "MoveFlagActor.h"
#include "TargetFlagActor.h"



AGroundTileActor::AGroundTileActor()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");

	GroundTileComponent = CreateDefaultSubobject<UStaticMeshComponent>("GroundTileComponent");
	GroundTileComponent->SetWorldScale3D(FVector(1.176470f));
	GroundTileComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	GroundTileComponent->SetCollisionResponseToAllChannels(ECR_Block);
	GroundTileComponent->SetCollisionObjectType(GameActorTrace);

	CloudTileComponent = CreateDefaultSubobject<UStaticMeshComponent>("CloudTileComponent");
	CloudTileComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CloudTileComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	CloudTileComponent->SetCollisionObjectType(GameActorTrace);
	CloudTileComponent->SetWorldScale3D(FVector(1.176470f));

	GroundTileComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	CloudTileComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	
	PrimaryActorTick.bCanEverTick = true;

	VisibilityCounter = 0;
}
void AGroundTileActor::On_Init()
{
	FlagTimer = 0.f;
	FlagActor = nullptr;
}
static float TimeOver = 3.f;
void AGroundTileActor::On_Tick(float DeltaSeconds)
{
	if (FlagActor)
	{
		FlagTimer += DeltaSeconds;
		if (FlagTimer >= TimeOver)
		{
			FlagActor->Destroy();
			FlagActor = nullptr;
			FlagTimer = 0.f;
		}
	}
	if (CloudTileComponent->GetVisibleFlag() && VisibilityCounter == 0)
	{
		CloudTileComponent->SetVisibility(false);
	}else if (!CloudTileComponent->GetVisibleFlag() && VisibilityCounter > 0)
	{
		CloudTileComponent->SetVisibility(true);
	}
}
void AGroundTileActor::On_Delete()
{
	Soldiers.Empty();
}

void AGroundTileActor::SetCloudVisible(bool InVisible)
{
	CloudTileComponent->SetVisibility(InVisible);
}
void AGroundTileActor::TrackAround()
{
	FVector ActorLocation = this->GetActorLocation();
	FVector GroundExtent = GroundTileComponent->GetBodySetup()->AggGeom.CalcAABB(FTransform(FVector::ZeroVector)).GetSize();
	
	TArray<AActor*> OverlapActors;
	TArray<TEnumAsByte<EObjectTypeQuery>> TrackObj = {UEngineTypes::ConvertToObjectType(GameActorTrace)};
	UKismetSystemLibrary::BoxOverlapActors(GetWorld(), ActorLocation, GroundExtent * 1.5f, TrackObj, AGameActor::StaticClass(), {this}, OverlapActors);
	
	AGameActor* SelfAator = this;
	FVector ForwardVector = GetActorForwardVector();
	FVector RightVector = GetActorRightVector();
	for (auto TemActor : OverlapActors)
	{
		if (TemActor->IsA<AGroundTileActor>())
		{
			float ForwardDot = FVector::DotProduct((TemActor->GetActorLocation() - ActorLocation).GetSafeNormal(), ForwardVector);
			float RightDot = FVector::DotProduct((TemActor->GetActorLocation() - ActorLocation).GetSafeNormal(), RightVector);
			if (FMath::IsNearlyEqual(ForwardDot, 1.f, FloatErrorTolerance))
			{ AroundActorMap.Add(Direction_Forward, Cast<AGameActor>(TemActor)); }
			else if (FMath::IsNearlyEqual(ForwardDot, -1.f, FloatErrorTolerance))
			{ AroundActorMap.Add(Direction_Back, Cast<AGameActor>(TemActor)); }
			else if (FMath::IsNearlyEqual(RightDot, 1.f, FloatErrorTolerance))
			{ AroundActorMap.Add(Direction_Right, Cast<AGameActor>(TemActor)); }
			else if (FMath::IsNearlyEqual(RightDot, -1.f, FloatErrorTolerance))
			{ AroundActorMap.Add(Direction_Left, Cast<AGameActor>(TemActor)); }
		}
		else if (TemActor->IsA<ACastleTileActor>())
		{
			AroundActorMap.Add(Direction_Other, Cast<AGameActor>(TemActor));
		}
	}

}
void AGroundTileActor::TrackSoldier()
{
	FVector ActorLocation = GetActorLocation();
	FBox    ActorBox = GroundTileComponent->GetBodySetup()->AggGeom.CalcAABB(FTransform(ActorLocation));
	FVector GroundSize = ActorBox.GetSize();

	TArray<AActor*> OverlapActors;
	TArray<TEnumAsByte<EObjectTypeQuery>> TrackObj = { UEngineTypes::ConvertToObjectType(SoldierTrace) };
	UKismetSystemLibrary::BoxOverlapActors(GetWorld(), ActorLocation, GroundSize * FVector(1.f,1.f,1.5f), TrackObj, ASoldierPawn::StaticClass(), { this }, OverlapActors);

	for (auto TemActor : OverlapActors)
	{
		if (ActorBox.ExpandBy(FVector::ZeroVector,FVector(0.f,0.f,250.f)).IsInside(TemActor->GetActorLocation()))
		{
			ASoldierPawn * TemSoldier = Cast<ASoldierPawn>(TemActor);
			AddSoldier(TemSoldier);
			TemSoldier->SetOriginGroundTile(this);
		}
	}
}
void AGroundTileActor::AddSoldier(ASoldierPawn * InSoldier)
{
	Soldiers.Add(InSoldier);
}
void AGroundTileActor::RemoveSoldier(ASoldierPawn * InSoldier)
{
	Soldiers.Remove(InSoldier);
}
bool AGroundTileActor::IsContain(ASoldierPawn * InSoldier)
{
	return Soldiers.Contains(InSoldier);
}
void AGroundTileActor::ShowFlags(bool InMoveFlag, bool InTargetFlag)
{
	
	if (InMoveFlag)
	{
		//0 : left:		FVector(0, -60, 0)		FRotator(0, 90, 0)
		//1 : Forward : FVector(60, 0, 0)		FRotator(0, 180, 0)
		//2 : Right :	FVector(0, 60, 0)		FRotator(0, -90, 0)
		//3 : Back :	FVector(-60, 0, 0)		FRotator(0, 0, 0)

		if (FlagActor){ FlagActor->Destroy();}
		UClass* FlagClass = LoadClass<AMoveFlagActor>(this, TEXT("/Game/Blueprint/MoveFlag_BP.MoveFlag_BP_C"));
		AMoveFlagActor * MoveActor = GetWorld()->SpawnActor<AMoveFlagActor>(FlagClass);
		MoveActor->SetActorLocation(GetActorLocation());
		if (AroundActorMap.Contains(Direction_Left))
		{ MoveActor->MeshComponent->AddInstance(FTransform(FRotator(0, 90, 0), FVector(0, -60, 0))); }
		if (AroundActorMap.Contains(Direction_Forward))
		{ MoveActor->MeshComponent->AddInstance(FTransform(FRotator(0, 180, 0), FVector(60, 0, 0))); }
		if (AroundActorMap.Contains(Direction_Right))
		{ MoveActor->MeshComponent->AddInstance(FTransform(FRotator(0, -90, 0), FVector(0, 60, 0))); }
		if (AroundActorMap.Contains(Direction_Back))
		{ MoveActor->MeshComponent->AddInstance(FTransform(FRotator(0, 0, 0), FVector(-60, 0, 0))); }
		FlagActor= MoveActor;
	}else if (InTargetFlag && !HaveSoldiers())
	{
		if (FlagActor) { FlagActor->Destroy(); }
		UClass* FlagClass = LoadClass<ATargetFlagActor>(this, TEXT("/Game/Blueprint/TargetFlag_BP.TargetFlag_BP_C"));
		FlagActor = GetWorld()->SpawnActor<ATargetFlagActor>(FlagClass,GetActorLocation(),GetActorRotation());
		
	}
	
}
AGroundTileActor* AGroundTileActor::GetAroundTileActorByDistance(int32 InDistance, DirectionEnum InDir)
{
	AGroundTileActor* TemTile = this;
	int index = 1;
	while (index <= InDistance)
	{
		if (TemTile && TemTile->AroundActorMap.Contains(InDir))
		{
			TemTile = (AGroundTileActor*)TemTile->AroundActorMap[InDir];
		}
		++index;
	}
	if (TemTile != this){return TemTile;}

	return nullptr;
}