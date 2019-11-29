#pragma once

#include "CoreMinimal.h"

#include "UObject/GCObject.h"


class FPrimitiveDrawInterface;
class ULandscapeInfo;
class ULandscapeLayerInfoObject;
class UMaterialInstance;
class UMaterialInterface;


struct FCLandscapeToolInteractorPosition
{
	// Stored in heightmap space.
	FVector2D Position;
	bool bModifierPressed;

	FCLandscapeToolInteractorPosition(FVector2D InPosition, const bool bInModifierPressed)
		: Position(InPosition)
		, bModifierPressed(bInModifierPressed)
	{
	}
};

enum class ECLandscapeBrushType
{
	Normal = 0,
	Alpha,
	Component,
	Gizmo,
	Splines
};

class FCLandscapeBrushData
{
protected:
	FIntRect Bounds;
	TArray<float> BrushAlpha;

public:
	FCLandscapeBrushData()
		: Bounds()
	{
	}

	FCLandscapeBrushData(FIntRect InBounds)
		: Bounds(InBounds)
	{
		BrushAlpha.SetNumZeroed(Bounds.Area());
	}

	FIntRect GetBounds() const
	{
		return Bounds;
	}

	// For compatibility with older landscape code that uses inclusive bounds in 4 int32s
	void GetInclusiveBounds(int32& X1, int32& Y1, int32& X2, int32& Y2) const
	{
		X1 = Bounds.Min.X;
		Y1 = Bounds.Min.Y;
		X2 = Bounds.Max.X - 1;
		Y2 = Bounds.Max.Y - 1;
	}

	float* GetDataPtr(FIntPoint Position)
	{
		return BrushAlpha.GetData() + (Position.Y - Bounds.Min.Y) * Bounds.Width() + (Position.X - Bounds.Min.X);
	}
	const float* GetDataPtr(FIntPoint Position) const
	{
		return BrushAlpha.GetData() + (Position.Y - Bounds.Min.Y) * Bounds.Width() + (Position.X - Bounds.Min.X);
	}

	FORCEINLINE explicit operator bool() const
	{
		return BrushAlpha.Num() != 0;
	}

	FORCEINLINE bool operator!() const
	{
		return !(bool)*this;
	}
};

class EDITLANDSCAPE_API FCLandscapeBrush : public FGCObject
{
public:
	
	virtual FCLandscapeBrushData ApplyBrush(const TArray<FCLandscapeToolInteractorPosition>& InteractorPositions) = 0;
	virtual void Tick(float DeltaTime) {};
	virtual ~FCLandscapeBrush() {}
	virtual ECLandscapeBrushType GetBrushType() { return ECLandscapeBrushType::Normal; }

	// FGCObject interface
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override {}
};


namespace ECLandscapeToolTargetType
{
	enum Type : int8
	{
		Heightmap = 0,
		Weightmap = 1,
		Visibility = 2,

		Invalid = -1, // only valid for LandscapeEdMode->CurrentToolTarget.TargetType
	};
}


struct FCLandscapeToolTarget
{
	TWeakObjectPtr<ULandscapeInfo> LandscapeInfo;
	ECLandscapeToolTargetType::Type TargetType;
	TWeakObjectPtr<ULandscapeLayerInfoObject> LayerInfo;
	FName LayerName;
	int32 CurrentProceduralLayerIndex;

	FCLandscapeToolTarget()
		: LandscapeInfo()
		, TargetType(ECLandscapeToolTargetType::Heightmap)
		, LayerInfo()
		, LayerName(NAME_None)
		, CurrentProceduralLayerIndex(INDEX_NONE)
	{
	}
};