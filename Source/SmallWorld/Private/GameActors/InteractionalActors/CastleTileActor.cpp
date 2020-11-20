#include "CastleTileActor.h"
#include "GroundTileActor.h"



ACastleTileActor::ACastleTileActor()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");

	CastleTileComponent = CreateDefaultSubobject<UStaticMeshComponent>("CastleTileComponent");
	CastleTileComponent->SetWorldScale3D(FVector(1.212121f));
	CastleTileComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CastleTileComponent->SetCollisionResponseToAllChannels(ECR_Block);
	CastleTileComponent->SetCollisionObjectType(GameActorTrace);

	CloudTileComponent = CreateDefaultSubobject<UInstancedStaticMeshComponent>("CloudTileComponent");
	CloudTileComponent->SetWorldScale3D(FVector(1.176470f));
	CloudTileComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CloudTileComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	CloudTileComponent->SetCollisionObjectType(GameActorTrace);

	CastleTileComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	CloudTileComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);


}
void ACastleTileActor::On_Init()
{


}
void ACastleTileActor::On_Tick(float DeltaSeconds)
{

}
void ACastleTileActor::On_Delete()
{

}
void ACastleTileActor::TrackAround()
{
	FVector ActorLocation = GetActorLocation();
	FVector GroundExtent = CastleTileComponent->GetBodySetup()->AggGeom.CalcAABB(FTransform(FVector::ZeroVector)).GetSize();

	TArray<AActor*> OverlapActors;
	TArray<TEnumAsByte<EObjectTypeQuery>> TrackObj = { UEngineTypes::ConvertToObjectType(GameActorTrace) };
	UKismetSystemLibrary::BoxOverlapActors(GetWorld(), ActorLocation, GroundExtent * 1.2f, TrackObj, AGameActor::StaticClass(), { this }, OverlapActors);

	for (auto TemActor : OverlapActors)
	{
		if (TemActor->IsA<AGroundTileActor>())
		{
			AroundActorArray.Add(Cast<AGroundTileActor>(TemActor));
		}
	}
}