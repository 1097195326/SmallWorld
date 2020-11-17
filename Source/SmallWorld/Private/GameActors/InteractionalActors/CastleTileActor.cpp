#include "CastleTileActor.h"
#include "GroundTileActor.h"



ACastleTileActor::ACastleTileActor()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");

	CastleTileComponent = CreateDefaultSubobject<UStaticMeshComponent>("CastleTileComponent");
	CloudTileComponent = CreateDefaultSubobject<UInstancedStaticMeshComponent>("CloudTileComponent");

	CastleTileComponent->SetWorldScale3D(FVector(1.212121f));
	CloudTileComponent->SetWorldScale3D(FVector(1.176470f));

	CollisionBoxComponent = CreateDefaultSubobject<UBoxComponent>("CollisionBoxComponent");
	CollisionBoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionBoxComponent->SetCollisionResponseToAllChannels(ECR_Block);
	CollisionBoxComponent->SetCollisionObjectType(GameActorTrace);


	CastleTileComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	CloudTileComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	CollisionBoxComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);


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