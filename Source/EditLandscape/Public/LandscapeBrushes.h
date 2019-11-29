#pragma once

#include "LandscapeToolInterface.h"

#include "CoreMinimal.h"
#include "Materials/Material.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialInstanceConstant.h"
#include "EngineUtils.h"
#include "LandscapeProxy.h"
#include "LandscapeEdit.h"
#include "LandscapeRender.h"


class FLandscapeBrushCircle : public FLandscapeBrush
{
	TSet<ULandscapeComponent*> BrushMaterialComponents;
	TArray<UMaterialInstanceDynamic*> BrushMaterialFreeInstances;

protected:
	TMap<ULandscapeComponent*, UMaterialInstanceDynamic*> BrushMaterialInstanceMap;

	virtual float CalculateFalloff(float Distance, float Radius, float Falloff) = 0;

	ULandscapeInfo* LandscapeInfo;
	float		BrushRadius;
	float		BrushFalloff;
public:
	FLandscapeBrushCircle(ULandscapeInfo* UseLandscapeInfo, float Radius, float Falloff):
		LandscapeInfo(UseLandscapeInfo),
		BrushRadius(Radius),
		BrushFalloff(Falloff)
	{
	}
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;
	virtual FLandscapeBrushData ApplyBrush(const TArray<FLandscapeToolInteractorPosition>& InInteractorPositions) override;
};


class FLandscapeBrushCircle_Linear : public FLandscapeBrushCircle
{
protected:
	virtual float CalculateFalloff(float Distance, float Radius, float Falloff) override;

public:
	FLandscapeBrushCircle_Linear(ULandscapeInfo* UseLandscapeInfo, float Radius, float Falloff)
		: FLandscapeBrushCircle(UseLandscapeInfo, Radius, Falloff)
	{
	}
};


class FLandscapeBrushCircle_Smooth : public FLandscapeBrushCircle_Linear
{
protected:
	
	virtual float CalculateFalloff(float Distance, float Radius, float Falloff) override;

public:
	FLandscapeBrushCircle_Smooth(ULandscapeInfo* UseLandscapeInfo, float Radius, float Falloff)
		: FLandscapeBrushCircle_Linear(UseLandscapeInfo, Radius, Falloff)
	{
	}
	
};
