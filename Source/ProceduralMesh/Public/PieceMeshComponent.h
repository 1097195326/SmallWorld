#pragma once

#include "Components/MeshComponent.h"
#include "PrimitiveSceneProxy.h"
#include "PieceMeshComponent.generated.h"


UCLASS()
class PROCEDURALMESH_API UPieceMeshComponent : public UMeshComponent
{
	GENERATED_BODY()

public:
	UPieceMeshComponent();

	virtual FPrimitiveSceneProxy* CreateSceneProxy() override;
};

class FPieceMeshComponentScenProxy : public FPrimitiveSceneProxy
{
public:
	FPieceMeshComponentScenProxy(UPrimitiveComponent * Component);

	virtual uint32 GetMemoryFootprint() const override;
	virtual void GetDynamicMeshElements(const TArray<const FSceneView *>& Views, const FSceneViewFamily& ViewFamily, uint32 VisibilityMap, class FMeshElementCollector& Collector) const override;
	virtual FPrimitiveViewRelevance GetViewRelevance(const FSceneView* View) const override;
	virtual SIZE_T GetTypeHash() const override;
};
