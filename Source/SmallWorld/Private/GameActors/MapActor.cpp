#include "MapActor.h"
//
//AMapActor::AMapActor()
//{
//	RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");
//
//	GroundMeshComponent = CreateDefaultSubobject<UInstancedStaticMeshComponent>("GroundMeshComponent");
//	CloudMeshComponent = CreateDefaultSubobject<UInstancedStaticMeshComponent>("CloudMeshComponent");
//	FenceMeshComponent = CreateDefaultSubobject<UInstancedStaticMeshComponent>("FenceMeshComponent");
//
//	GroundMeshComponent->AttachToComponent(RootComponent,FAttachmentTransformRules::KeepRelativeTransform);
//	CloudMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
//	FenceMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
//
//
//}
//void AMapActor::On_Init()
//{
//
//}
//void AMapActor::On_Tick(float DeltaSeconds)
//{
//
//}
//void AMapActor::On_Delete()
//{
//
//}
//int32 AMapActor::AddGroupInstance(const FVector& InLocation)
//{
//	AddCloudInstance(InLocation);
//	return std::move(GroundMeshComponent->AddInstance(FTransform(InLocation)));
//}
//int32 AMapActor::AddCloudInstance(const FVector& InLocation)
//{
//	return 	std::move(CloudMeshComponent->AddInstance(FTransform(InLocation)));
//}
//FVector AMapActor::GetGroupInstanceLocation(const int32 & inIndex)
//{
//	FTransform TemTrans;
//	GroundMeshComponent->GetInstanceTransform(inIndex, TemTrans, true);
//	return TemTrans.GetLocation();
//}
//void AMapActor::SetCloudInstanceVisible(const int32 & InIndex, const bool & InIsVisible)
//{
//	FTransform TemTrans;
//	CloudMeshComponent->GetInstanceTransform(InIndex, TemTrans);
//	FVector PreLocation = TemTrans.GetLocation();
//	PreLocation.Z = 0;
//	TemTrans.SetLocation(PreLocation);
//	CloudMeshComponent->UpdateInstanceTransform(InIndex, TemTrans);
//}