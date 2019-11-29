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


class EDITLANDSCAPE_API FCLandscapeBrushCircle : public FCLandscapeBrush
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
	FCLandscapeBrushCircle(ULandscapeInfo* UseLandscapeInfo, float Radius, float Falloff):
		LandscapeInfo(UseLandscapeInfo),
		BrushRadius(Radius),
		BrushFalloff(Falloff)
	{
	}
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;
	virtual FCLandscapeBrushData ApplyBrush(const TArray<FCLandscapeToolInteractorPosition>& InInteractorPositions) override;
};


class EDITLANDSCAPE_API FCLandscapeBrushCircle_Linear : public FCLandscapeBrushCircle
{
protected:
	virtual float CalculateFalloff(float Distance, float Radius, float Falloff) override;

public:
	FCLandscapeBrushCircle_Linear(ULandscapeInfo* UseLandscapeInfo, float Radius, float Falloff)
		: FCLandscapeBrushCircle(UseLandscapeInfo, Radius, Falloff)
	{
	}
};


class EDITLANDSCAPE_API FCLandscapeBrushCircle_Smooth : public FCLandscapeBrushCircle_Linear
{
protected:
	
	virtual float CalculateFalloff(float Distance, float Radius, float Falloff) override;

public:
	FCLandscapeBrushCircle_Smooth(ULandscapeInfo* UseLandscapeInfo, float Radius, float Falloff)
		: FCLandscapeBrushCircle_Linear(UseLandscapeInfo, Radius, Falloff)
	{
	}
	
};
