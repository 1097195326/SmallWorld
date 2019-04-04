#include "StaticPlaneMeshComponent.h"



UStaticPlaneMeshComponent::UStaticPlaneMeshComponent()
{
}
FPrimitiveSceneProxy* UStaticPlaneMeshComponent::CreateSceneProxy()
{
	return new FPlaneMeshComponentScenProxy(this);
}

// --------------

FPlaneMeshComponentScenProxy::FPlaneMeshComponentScenProxy(UPrimitiveComponent * Component)
	:FPrimitiveSceneProxy(Component)
{

}
uint32 FPlaneMeshComponentScenProxy::GetMemoryFootprint() const
{
	return (sizeof(*this) + GetAllocatedSize());
}

void FPlaneMeshComponentScenProxy::GetDynamicMeshElements(const TArray<const FSceneView *>& Views, const FSceneViewFamily& ViewFamily, uint32 VisibilityMap, class FMeshElementCollector& Collector) const
{
	FBox bb = FBox(FVector(-100.f), FVector(100.f));
	DrawWireBox(Collector.GetPDI(0), GetLocalToWorld(), bb, FLinearColor::Red, ESceneDepthPriorityGroup::SDPG_Foreground, 10.f);

}
FPrimitiveViewRelevance FPlaneMeshComponentScenProxy::GetViewRelevance(const FSceneView* View) const
{
	FPrimitiveViewRelevance Result;
	Result.bDrawRelevance = IsShown(View);
	Result.bDynamicRelevance = true;
	Result.bShadowRelevance = IsShadowCast(View);
	Result.bEditorPrimitiveRelevance = UseEditorCompositing(View);
	return Result;
}
SIZE_T FPlaneMeshComponentScenProxy::GetTypeHash() const
{
	static SIZE_T UniquePointer;
	return reinterpret_cast<SIZE_T>(&UniquePointer);
}