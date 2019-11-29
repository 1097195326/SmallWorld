#pragma once


#include "CoreMinimal.h"
#include "UObject/GCObject.h"
#include "LandscapeProxy.h"
#include "LandscapeToolInterface.h"
#include "LandscapeEdit.h"
#include "LandscapeComponent.h"
#include "LandscapeDataAccess.h"
#include "LandscapeHeightfieldCollisionComponent.h"
#include "InstancedFoliageActor.h"


template<class Accessor, typename AccessorType>
struct TCLandscapeEditCache
{
public:
	typedef AccessorType DataType;
	Accessor DataAccess;

	TCLandscapeEditCache(const FCLandscapeToolTarget& InTarget)
		: DataAccess(InTarget)
		, Valid(false)
	{
	}

	// X2/Y2 Coordinates are "inclusive" max values
	void CacheData(int32 X1, int32 Y1, int32 X2, int32 Y2)
	{
		if (!Valid)
		{
			if (Accessor::bUseInterp)
			{
				ValidX1 = CachedX1 = X1;
				ValidY1 = CachedY1 = Y1;
				ValidX2 = CachedX2 = X2;
				ValidY2 = CachedY2 = Y2;

				DataAccess.GetData(ValidX1, ValidY1, ValidX2, ValidY2, CachedData);
				if (!ensureMsgf(ValidX1 <= ValidX2 && ValidY1 <= ValidY2, TEXT("Invalid cache area: X(%d-%d), Y(%d-%d) from region X(%d-%d), Y(%d-%d)"), ValidX1, ValidX2, ValidY1, ValidY2, X1, X2, Y1, Y2))
				{
					Valid = false;
					return;
				}
			}
			else
			{
				CachedX1 = X1;
				CachedY1 = Y1;
				CachedX2 = X2;
				CachedY2 = Y2;

				DataAccess.GetDataFast(CachedX1, CachedY1, CachedX2, CachedY2, CachedData);
			}

			OriginalData = CachedData;

			Valid = true;
		}
		else
		{
			// Extend the cache area if needed
			if (X1 < CachedX1)
			{
				if (Accessor::bUseInterp)
				{
					int32 x1 = X1;
					int32 x2 = ValidX1;
					int32 y1 = FMath::Min<int32>(Y1, CachedY1);
					int32 y2 = FMath::Max<int32>(Y2, CachedY2);

					DataAccess.GetData(x1, y1, x2, y2, CachedData);
					ValidX1 = FMath::Min<int32>(x1, ValidX1);
				}
				else
				{
					DataAccess.GetDataFast(X1, CachedY1, CachedX1 - 1, CachedY2, CachedData);
				}

				CacheOriginalData(X1, CachedY1, CachedX1 - 1, CachedY2);
				CachedX1 = X1;
			}

			if (X2 > CachedX2)
			{
				if (Accessor::bUseInterp)
				{
					int32 x1 = ValidX2;
					int32 x2 = X2;
					int32 y1 = FMath::Min<int32>(Y1, CachedY1);
					int32 y2 = FMath::Max<int32>(Y2, CachedY2);

					DataAccess.GetData(x1, y1, x2, y2, CachedData);
					ValidX2 = FMath::Max<int32>(x2, ValidX2);
				}
				else
				{
					DataAccess.GetDataFast(CachedX2 + 1, CachedY1, X2, CachedY2, CachedData);
				}
				CacheOriginalData(CachedX2 + 1, CachedY1, X2, CachedY2);
				CachedX2 = X2;
			}

			if (Y1 < CachedY1)
			{
				if (Accessor::bUseInterp)
				{
					int32 x1 = CachedX1;
					int32 x2 = CachedX2;
					int32 y1 = Y1;
					int32 y2 = ValidY1;

					DataAccess.GetData(x1, y1, x2, y2, CachedData);
					ValidY1 = FMath::Min<int32>(y1, ValidY1);
				}
				else
				{
					DataAccess.GetDataFast(CachedX1, Y1, CachedX2, CachedY1 - 1, CachedData);
				}
				CacheOriginalData(CachedX1, Y1, CachedX2, CachedY1 - 1);
				CachedY1 = Y1;
			}

			if (Y2 > CachedY2)
			{
				if (Accessor::bUseInterp)
				{
					int32 x1 = CachedX1;
					int32 x2 = CachedX2;
					int32 y1 = ValidY2;
					int32 y2 = Y2;

					DataAccess.GetData(x1, y1, x2, y2, CachedData);
					ValidY2 = FMath::Max<int32>(y2, ValidY2);
				}
				else
				{
					DataAccess.GetDataFast(CachedX1, CachedY2 + 1, CachedX2, Y2, CachedData);
				}

				CacheOriginalData(CachedX1, CachedY2 + 1, CachedX2, Y2);
				CachedY2 = Y2;
			}
		}
	}

	AccessorType* GetValueRef(int32 LandscapeX, int32 LandscapeY)
	{
		return CachedData.Find(FIntPoint(LandscapeX, LandscapeY));
	}

	float GetValue(float LandscapeX, float LandscapeY)
	{
		int32 X = FMath::FloorToInt(LandscapeX);
		int32 Y = FMath::FloorToInt(LandscapeY);
		AccessorType* P00 = CachedData.Find(FIntPoint(X, Y));
		AccessorType* P10 = CachedData.Find(FIntPoint(X + 1, Y));
		AccessorType* P01 = CachedData.Find(FIntPoint(X, Y + 1));
		AccessorType* P11 = CachedData.Find(FIntPoint(X + 1, Y + 1));

		// Search for nearest value if missing data
		float V00 = P00 ? *P00 : (P10 ? *P10 : (P01 ? *P01 : (P11 ? *P11 : 0.0f)));
		float V10 = P10 ? *P10 : (P00 ? *P00 : (P11 ? *P11 : (P01 ? *P01 : 0.0f)));
		float V01 = P01 ? *P01 : (P00 ? *P00 : (P11 ? *P11 : (P10 ? *P10 : 0.0f)));
		float V11 = P11 ? *P11 : (P10 ? *P10 : (P01 ? *P01 : (P00 ? *P00 : 0.0f)));

		return FMath::Lerp(
			FMath::Lerp(V00, V10, LandscapeX - X),
			FMath::Lerp(V01, V11, LandscapeX - X),
			LandscapeY - Y);
	}

	FVector GetNormal(int32 X, int32 Y)
	{
		AccessorType* P00 = CachedData.Find(FIntPoint(X, Y));
		AccessorType* P10 = CachedData.Find(FIntPoint(X + 1, Y));
		AccessorType* P01 = CachedData.Find(FIntPoint(X, Y + 1));
		AccessorType* P11 = CachedData.Find(FIntPoint(X + 1, Y + 1));

		// Search for nearest value if missing data
		float V00 = P00 ? *P00 : (P10 ? *P10 : (P01 ? *P01 : (P11 ? *P11 : 0.0f)));
		float V10 = P10 ? *P10 : (P00 ? *P00 : (P11 ? *P11 : (P01 ? *P01 : 0.0f)));
		float V01 = P01 ? *P01 : (P00 ? *P00 : (P11 ? *P11 : (P10 ? *P10 : 0.0f)));
		float V11 = P11 ? *P11 : (P10 ? *P10 : (P01 ? *P01 : (P00 ? *P00 : 0.0f)));

		FVector Vert00 = FVector(0.0f, 0.0f, V00);
		FVector Vert01 = FVector(0.0f, 1.0f, V01);
		FVector Vert10 = FVector(1.0f, 0.0f, V10);
		FVector Vert11 = FVector(1.0f, 1.0f, V11);

		FVector FaceNormal1 = ((Vert00 - Vert10) ^ (Vert10 - Vert11)).GetSafeNormal();
		FVector FaceNormal2 = ((Vert11 - Vert01) ^ (Vert01 - Vert00)).GetSafeNormal();
		return (FaceNormal1 + FaceNormal2).GetSafeNormal();
	}

	void SetValue(int32 LandscapeX, int32 LandscapeY, AccessorType Value)
	{
		CachedData.Add(FIntPoint(LandscapeX, LandscapeY), Forward<AccessorType>(Value));
	}

	bool IsZeroValue(const FVector& Value)
	{
		return (FMath::IsNearlyZero(Value.X) && FMath::IsNearlyZero(Value.Y));
	}

	bool IsZeroValue(const FVector2D& Value)
	{
		return (FMath::IsNearlyZero(Value.X) && FMath::IsNearlyZero(Value.Y));
	}

	bool IsZeroValue(const uint16& Value)
	{
		return Value == 0;
	}

	bool IsZeroValue(const uint8& Value)
	{
		return Value == 0;
	}

	// X2/Y2 Coordinates are "inclusive" max values
	bool GetCachedData(int32 X1, int32 Y1, int32 X2, int32 Y2, TArray<AccessorType>& OutData)
	{
		const int32 XSize = (1 + X2 - X1);
		const int32 YSize = (1 + Y2 - Y1);
		const int32 NumSamples = XSize * YSize;
		OutData.Empty(NumSamples);
		OutData.AddUninitialized(NumSamples);
		bool bHasNonZero = false;

		for (int32 Y = Y1; Y <= Y2; Y++)
		{
			const int32 YOffset = (Y - Y1) * XSize;
			for (int32 X = X1; X <= X2; X++)
			{
				const int32 XYOffset = YOffset + (X - X1);
				AccessorType* Ptr = GetValueRef(X, Y);
				if (Ptr)
				{
					OutData[XYOffset] = *Ptr;
					if (!IsZeroValue(*Ptr))
					{
						bHasNonZero = true;
					}
				}
				else
				{
					OutData[XYOffset] = (AccessorType)0;
				}
			}
		}

		return bHasNonZero;
	}

	// X2/Y2 Coordinates are "inclusive" max values
	void SetCachedData(int32 X1, int32 Y1, int32 X2, int32 Y2, TArray<AccessorType>& Data, ELandscapeLayerPaintingRestriction PaintingRestriction = ELandscapeLayerPaintingRestriction::None)
	{
		checkSlow(Data.Num() == (1 + Y2 - Y1) * (1 + X2 - X1));

		// Update cache
		for (int32 Y = Y1; Y <= Y2; Y++)
		{
			for (int32 X = X1; X <= X2; X++)
			{
				SetValue(X, Y, Data[(X - X1) + (Y - Y1)*(1 + X2 - X1)]);
			}
		}

		// Update real data
		DataAccess.SetData(X1, Y1, X2, Y2, Data.GetData(), PaintingRestriction);
	}

	// Get the original data before we made any changes with the SetCachedData interface.
	// X2/Y2 Coordinates are "inclusive" max values
	void GetOriginalData(int32 X1, int32 Y1, int32 X2, int32 Y2, TArray<AccessorType>& OutOriginalData)
	{
		int32 NumSamples = (1 + X2 - X1)*(1 + Y2 - Y1);
		OutOriginalData.Empty(NumSamples);
		OutOriginalData.AddUninitialized(NumSamples);

		for (int32 Y = Y1; Y <= Y2; Y++)
		{
			for (int32 X = X1; X <= X2; X++)
			{
				AccessorType* Ptr = OriginalData.Find(FIntPoint(X, Y));
				if (Ptr)
				{
					OutOriginalData[(X - X1) + (Y - Y1)*(1 + X2 - X1)] = *Ptr;
				}
			}
		}
	}

	void Flush()
	{
		DataAccess.Flush();
	}

private:
	// X2/Y2 Coordinates are "inclusive" max values
	void CacheOriginalData(int32 X1, int32 Y1, int32 X2, int32 Y2)
	{
		for (int32 Y = Y1; Y <= Y2; Y++)
		{
			for (int32 X = X1; X <= X2; X++)
			{
				FIntPoint Key = FIntPoint(X, Y);
				AccessorType* Ptr = CachedData.Find(Key);
				if (Ptr)
				{
					check(OriginalData.Find(Key) == NULL);
					OriginalData.Add(Key, *Ptr);
				}
			}
		}
	}

	TMap<FIntPoint, AccessorType> CachedData;
	TMap<FIntPoint, AccessorType> OriginalData;

	bool Valid;

	int32 CachedX1;
	int32 CachedY1;
	int32 CachedX2;
	int32 CachedY2;

	// To store valid region....
	int32 ValidX1, ValidX2, ValidY1, ValidY2;
};


template<bool bInUseInterp, bool bInUseTotalNormalize>
struct FCAlphamapAccessorTool : public FAlphamapAccessor<bInUseInterp, bInUseTotalNormalize>
{
	FCAlphamapAccessorTool(ULandscapeInfo* InLandscapeInfo, ULandscapeLayerInfoObject* InLayerInfo)
		: FAlphamapAccessor<bInUseInterp, bInUseTotalNormalize>(InLandscapeInfo, InLayerInfo)
	{}

	FCAlphamapAccessorTool(const FCLandscapeToolTarget& InTarget)
		: FAlphamapAccessor<bInUseInterp, bInUseTotalNormalize>(InTarget.LandscapeInfo.Get(), InTarget.LayerInfo.Get())
	{
	}
};


struct FCLandscapeAlphaCache : public TCLandscapeEditCache<FCAlphamapAccessorTool<true, false>, uint8>
{
	static uint8 ClampValue(int32 Value) { return FMath::Clamp(Value, 0, 255); }

	FCLandscapeAlphaCache(const FCLandscapeToolTarget& InTarget)
		: TCLandscapeEditCache<FCAlphamapAccessorTool<true, false>, uint8>(InTarget)
	{
	}
};


struct FCWeightmapToolTarget
{
	typedef FCLandscapeAlphaCache CacheClass;
	static const ECLandscapeToolTargetType::Type TargetType = ECLandscapeToolTargetType::Weightmap;

	static float StrengthMultiplier(ULandscapeInfo* LandscapeInfo, float BrushRadius)
	{
		return 255.0f;
	}

	static FMatrix ToWorldMatrix(ULandscapeInfo* LandscapeInfo) { return FMatrix::Identity; }
	static FMatrix FromWorldMatrix(ULandscapeInfo* LandscapeInfo) { return FMatrix::Identity; }
};


class FCLandscapeToolStrokeBase : protected FGCObject
{
public:
	// Whether to call Apply() every frame even if the mouse hasn't moved
	enum { UseContinuousApply = false };

	// This is also the expected signature of derived class constructor used by FLandscapeToolBase
	FCLandscapeToolStrokeBase(const FCLandscapeToolTarget& InTarget)
		: Target(InTarget)
		, LandscapeInfo(InTarget.LandscapeInfo.Get())
	{
	}

	// Signature of Apply() method for derived strokes
	// void Apply(FEditorViewportClient* ViewportClient, FLandscapeBrush* Brush, const ULandscapeEditorObject* UISettings, const TArray<FLandscapeToolMousePosition>& MousePositions);

	virtual void AddReferencedObjects(FReferenceCollector& Collector) override
	{
		Collector.AddReferencedObject(LandscapeInfo);
	}

protected:
	const FCLandscapeToolTarget& Target;
	ULandscapeInfo* LandscapeInfo;
};
