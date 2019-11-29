#pragma once

#include "CoreMinimal.h"

#include "UObject/GCObject.h"


class FPrimitiveDrawInterface;
class ULandscapeInfo;
class ULandscapeLayerInfoObject;
class UMaterialInstance;
class UMaterialInterface;


struct FLandscapeToolInteractorPosition
{
	// Stored in heightmap space.
	FVector2D Position;
	bool bModifierPressed;

	FLandscapeToolInteractorPosition(FVector2D InPosition, const bool bInModifierPressed)
		: Position(InPosition)
		, bModifierPressed(bInModifierPressed)
	{
	}
};

enum class ELandscapeBrushType
{
	Normal = 0,
	Alpha,
	Component,
	Gizmo,
	Splines
};

class FLandscapeBrushData
{
protected:
	FIntRect Bounds;
	TArray<float> BrushAlpha;

public:
	FLandscapeBrushData()
		: Bounds()
	{
	}

	FLandscapeBrushData(FIntRect InBounds)
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

class FLandscapeBrush : public FGCObject
{
public:
	
	virtual FLandscapeBrushData ApplyBrush(const TArray<FLandscapeToolInteractorPosition>& InteractorPositions) = 0;
	virtual void Tick(float DeltaTime) {};
	virtual ~FLandscapeBrush() {}
	virtual ELandscapeBrushType GetBrushType() { return ELandscapeBrushType::Normal; }

	// FGCObject interface
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override {}
};


namespace ELandscapeToolTargetType
{
	enum Type : int8
	{
		Heightmap = 0,
		Weightmap = 1,
		Visibility = 2,

		Invalid = -1, // only valid for LandscapeEdMode->CurrentToolTarget.TargetType
	};
}


struct FLandscapeToolTarget
{
	TWeakObjectPtr<ULandscapeInfo> LandscapeInfo;
	ELandscapeToolTargetType::Type TargetType;
	TWeakObjectPtr<ULandscapeLayerInfoObject> LayerInfo;
	FName LayerName;
	int32 CurrentProceduralLayerIndex;

	FLandscapeToolTarget()
		: LandscapeInfo()
		, TargetType(ELandscapeToolTargetType::Heightmap)
		, LayerInfo()
		, LayerName(NAME_None)
		, CurrentProceduralLayerIndex(INDEX_NONE)
	{
	}
};