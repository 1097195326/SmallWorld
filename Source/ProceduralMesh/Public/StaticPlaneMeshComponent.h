#pragma once

#include "Components/MeshComponent.h"
#include "StaticPlaneMeshComponent.generated.h"


UCLASS()
class PROCEDURALMESH_API UStaticPlaneMeshComponent : public UMeshComponent
{
	GENERATED_BODY()

public:
	UStaticPlaneMeshComponent();

	virtual FPrimitiveSceneProxy* CreateSceneProxy() override;
};

class FPlaneMeshComponentScenProxy : public FPrimitiveSceneProxy
{
public:
	FPlaneMeshComponentScenProxy(UPrimitiveComponent * Component);

	virtual uint32 GetMemoryFootprint() const override;
	virtual void GetDynamicMeshElements(const TArray<const FSceneView *>& Views, const FSceneViewFamily& ViewFamily, uint32 VisibilityMap, class FMeshElementCollector& Collector) const override;
	virtual FPrimitiveViewRelevance GetViewRelevance(const FSceneView* View) const override;
	virtual SIZE_T GetTypeHash() const override;
};
