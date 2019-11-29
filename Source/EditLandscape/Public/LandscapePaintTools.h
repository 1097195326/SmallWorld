#pragma once

#include "LandscapeEditTool.h"


template<class ToolTarget>
class FCLandscapeToolStrokePaintBase : public FCLandscapeToolStrokeBase
{
public:
	FCLandscapeToolStrokePaintBase(const FCLandscapeToolTarget& InTarget)
		: FCLandscapeToolStrokeBase(InTarget)
		, Cache(InTarget)
	{
	}

protected:
	typename ToolTarget::CacheClass Cache;
};

class EDITLANDSCAPE_API FCLandscapeToolStrokePaint : public FCLandscapeToolStrokePaintBase<FCWeightmapToolTarget>
{
	typedef FCWeightmapToolTarget ToolTarget;

	TMap<FIntPoint, float> TotalInfluenceMap; // amount of time and weight the brush has spent on each vertex.

public:
	// Heightmap sculpt tool will continuously sculpt in the same location, weightmap paint tool doesn't
	enum { UseContinuousApply = false };

	FCLandscapeToolStrokePaint(const FCLandscapeToolTarget& InTarget)
		: FCLandscapeToolStrokePaintBase<FCWeightmapToolTarget>(InTarget)
	{
	}

	void Apply(FCLandscapeBrush* Brush, const TArray<FCLandscapeToolInteractorPosition>& InteractorPositions);
	
};