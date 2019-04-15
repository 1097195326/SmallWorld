#include "PieceMeshComponent.h"



UPieceMeshComponent::UPieceMeshComponent()
{
}
FPrimitiveSceneProxy* UPieceMeshComponent::CreateSceneProxy()
{
	return new FPieceMeshComponentScenProxy(this);
}

// --------------

FPieceMeshComponentScenProxy::FPieceMeshComponentScenProxy(UPrimitiveComponent * Component)
	:FPrimitiveSceneProxy(Component)
{

}
uint32 FPieceMeshComponentScenProxy::GetMemoryFootprint() const
{
	return (sizeof(*this) + GetAllocatedSize());
}

void FPieceMeshComponentScenProxy::GetDynamicMeshElements(const TArray<const FSceneView *>& Views, const FSceneViewFamily& ViewFamily, uint32 VisibilityMap, class FMeshElementCollector& Collector) const
{
	FBox bb = FBox(FVector(-100.f), FVector(100.f));
	DrawWireBox(Collector.GetPDI(0), GetLocalToWorld(), bb, FLinearColor::Red, ESceneDepthPriorityGroup::SDPG_Foreground, 10.f);

}
FPrimitiveViewRelevance FPieceMeshComponentScenProxy::GetViewRelevance(const FSceneView* View) const
{
	FPrimitiveViewRelevance Result;
	Result.bDrawRelevance = IsShown(View);
	Result.bDynamicRelevance = true;
	Result.bShadowRelevance = IsShadowCast(View);
	Result.bEditorPrimitiveRelevance = UseEditorCompositing(View);
	return Result;
}
SIZE_T FPieceMeshComponentScenProxy::GetTypeHash() const
{
	static SIZE_T UniquePointer;
	return reinterpret_cast<SIZE_T>(&UniquePointer);
}