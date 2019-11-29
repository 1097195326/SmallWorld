#pragma once

#include "LandscapeEditTool.h"


template<class ToolTarget>
class FLandscapeToolStrokePaintBase : public FLandscapeToolStrokeBase
{
public:
	FLandscapeToolStrokePaintBase(const FLandscapeToolTarget& InTarget)
		: FLandscapeToolStrokeBase(InTarget)
		, Cache(InTarget)
	{
	}

protected:
	typename ToolTarget::CacheClass Cache;
};

class FLandscapeToolStrokePaint : public FLandscapeToolStrokePaintBase<FWeightmapToolTarget>
{
	typedef FWeightmapToolTarget ToolTarget;

	TMap<FIntPoint, float> TotalInfluenceMap; // amount of time and weight the brush has spent on each vertex.

public:
	// Heightmap sculpt tool will continuously sculpt in the same location, weightmap paint tool doesn't
	enum { UseContinuousApply = false };

	FLandscapeToolStrokePaint(const FLandscapeToolTarget& InTarget)
		: FLandscapeToolStrokePaintBase<FWeightmapToolTarget>(InTarget)
	{
	}

	void Apply(FLandscapeBrush* Brush, const TArray<FLandscapeToolInteractorPosition>& InteractorPositions);
	
};