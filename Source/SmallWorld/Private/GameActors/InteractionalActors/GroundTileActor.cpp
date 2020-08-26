#include "GroundTileActor.h"
#include "Kismet/KismetSystemLibrary.h"
#include "CastleTileActor.h"
#include "SoldierPawn.h"

AGroundTileActor::AGroundTileActor()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");

	GroundTileComponent = CreateDefaultSubobject<UStaticMeshComponent>("GroundTileComponent");
	CloudTileComponent = CreateDefaultSubobject<UStaticMeshComponent>("CloudTileComponent");
	CollisionBoxComponent = CreateDefaultSubobject<UBoxComponent>("CollisionBoxComponent");

	GroundTileComponent->SetWorldScale3D(FVector(1.176470f));

	CloudTileComponent->SetWorldScale3D(FVector(1.176470f));
	CloudTileComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CloudTileComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	CloudTileComponent->SetCollisionObjectType(ECC_Visibility);

	GroundTileComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	CloudTileComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	CollisionBoxComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	Soldier = nullptr;
}
void AGroundTileActor::On_Init()
{


}
void AGroundTileActor::On_Tick(float DeltaSeconds)
{

}
void AGroundTileActor::On_Delete()
{
	Soldier = nullptr;
}
void AGroundTileActor::SetCloudVisible(bool InVisible)
{
	CloudTileComponent->SetVisibility(InVisible);
}
void AGroundTileActor::TrackAround()
{
	FVector ActorLocation = GetActorLocation();
	FVector GroundExtent = GroundTileComponent->GetBodySetup()->AggGeom.CalcAABB(FTransform(FVector::ZeroVector)).GetExtent();
	
	TArray<AActor*> OverlapActors;
	TArray<TEnumAsByte<EObjectTypeQuery>> TrackObj = {UEngineTypes::ConvertToObjectType(ECC_Visibility)};
	UKismetSystemLibrary::BoxOverlapActors(GetWorld(), ActorLocation, GroundExtent * 1.5f, TrackObj, AGameActor::StaticClass(), {this}, OverlapActors);
	
	FVector ForwardVector = GetActorForwardVector();
	FVector RightVector = GetActorRightVector();
	for (auto TemActor : OverlapActors)
	{
		if (TemActor->IsA<AGroundTileActor>())
		{
			float ForwardDot = FVector::DotProduct((TemActor->GetActorLocation() - ActorLocation).GetSafeNormal(), ForwardVector);
			float RightDot = FVector::DotProduct((TemActor->GetActorLocation() - ActorLocation).GetSafeNormal(), RightVector);
			if (FMath::IsNearlyEqual(ForwardDot, 1.f))
			{ AroundActorMap[Direction_Up] = Cast<AGameActor>(TemActor); }
			else if (FMath::IsNearlyEqual(ForwardDot, -1.f))
			{ AroundActorMap[Direction_Down] = Cast<AGameActor>(TemActor); }
			else if (FMath::IsNearlyEqual(RightDot, 1.f))
			{ AroundActorMap[Direction_Right] = Cast<AGameActor>(TemActor); }
			else if (FMath::IsNearlyEqual(RightDot, -1.f))
			{ AroundActorMap[Direction_Left] = Cast<AGameActor>(TemActor); }
		}
		else if (TemActor->IsA<ACastleTileActor>())
		{ AroundActorMap[Direction_Other] = Cast<AGameActor>(TemActor); }
	}

}
void AGroundTileActor::TrackSoldier()
{
	FVector ActorLocation = GetActorLocation();
	FBox    ActorBox = GroundTileComponent->GetBodySetup()->AggGeom.CalcAABB(FTransform(ActorLocation));
	FVector GroundSize = ActorBox.GetExtent();

	TArray<AActor*> OverlapActors;
	TArray<TEnumAsByte<EObjectTypeQuery>> TrackObj = { UEngineTypes::ConvertToObjectType(ECC_Visibility) };
	UKismetSystemLibrary::BoxOverlapActors(GetWorld(), ActorLocation, GroundSize * FVector(1.f,1.f,1.5f), TrackObj, ASoldierPawn::StaticClass(), { this }, OverlapActors);

	for (auto TemActor : OverlapActors)
	{
		if (ActorBox.ExpandBy(FVector::ZeroVector,FVector(0.f,0.f,50.f)).IsInside(TemActor->GetActorLocation()))
		{
			ASoldierPawn * TemSoldier = Cast<ASoldierPawn>(TemActor);
			SetSoldier(TemSoldier);
			TemSoldier->SetGroundTile(this);
			break;
		}
	}
}
void AGroundTileActor::SetSoldier(class ASoldierPawn * InSoldier)
{
	Soldier = InSoldier;
}