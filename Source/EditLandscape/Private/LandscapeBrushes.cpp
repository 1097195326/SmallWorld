#include "LandscapeBrushes.h"

void FCLandscapeBrushCircle::AddReferencedObjects(FReferenceCollector& Collector)
{
	// Allow any currently unused material instances to be GC'd
	BrushMaterialFreeInstances.Empty();

	Collector.AddReferencedObjects(BrushMaterialComponents);
	Collector.AddReferencedObjects(BrushMaterialInstanceMap);

	// If a user tool removes any components then we will have bad (null) entries in our TSet/TMap, remove them
	// We can't just call .Remove(nullptr) because the entries were hashed as non-null values so a hash lookup of nullptr won't find them
	for (auto It = BrushMaterialComponents.CreateIterator(); It; ++It)
	{
		if (*It == nullptr)
		{
			It.RemoveCurrent();
		}
	}
	for (auto It = BrushMaterialInstanceMap.CreateIterator(); It; ++It)
	{
		if (It->Key == nullptr || It->Value == nullptr)
		{
			It.RemoveCurrent();
		}
	}
}

FCLandscapeBrushData FCLandscapeBrushCircle::ApplyBrush(const TArray<FCLandscapeToolInteractorPosition>& InInteractorPositions)
{
	const float ScaleXY = FMath::Abs(LandscapeInfo->DrawScale.X);
	const float TotalRadius = BrushRadius / ScaleXY;
	const float Radius = (1.0f - BrushFalloff) * TotalRadius;
	const float Falloff = BrushFalloff * TotalRadius;

	// Cap number of mouse positions to a sensible number
	TArray<FCLandscapeToolInteractorPosition> InteractorPositions;
	if (InInteractorPositions.Num() > 10)
	{
		for (int32 i = 0; i < 10; ++i)
		{
			// Scale so we include the first and last of the input positions
			InteractorPositions.Add(InInteractorPositions[(i * (InInteractorPositions.Num() - 1)) / 9]);
		}
	}
	else
	{
		InteractorPositions = InInteractorPositions;
	}

	FIntRect Bounds;
	for (const FCLandscapeToolInteractorPosition& InteractorPosition : InteractorPositions)
	{
		FIntRect SpotBounds;
		SpotBounds.Min.X = FMath::FloorToInt(InteractorPosition.Position.X - TotalRadius);
		SpotBounds.Min.Y = FMath::FloorToInt(InteractorPosition.Position.Y - TotalRadius);
		SpotBounds.Max.X = FMath::CeilToInt(InteractorPosition.Position.X + TotalRadius);
		SpotBounds.Max.Y = FMath::CeilToInt(InteractorPosition.Position.Y + TotalRadius);

		if (Bounds.IsEmpty())
		{
			Bounds = SpotBounds;
		}
		else
		{
			Bounds.Min = Bounds.Min.ComponentMin(SpotBounds.Min);
			Bounds.Max = Bounds.Max.ComponentMax(SpotBounds.Max);
		}
	}

	// Clamp to landscape bounds
	int32 MinX, MaxX, MinY, MaxY;
	if (!ensure(LandscapeInfo->GetLandscapeExtent(MinX, MinY, MaxX, MaxY)))
	{
		// Landscape has no components somehow
		return FCLandscapeBrushData();
	}
	Bounds.Clip(FIntRect(MinX, MinY, MaxX + 1, MaxY + 1));

	FCLandscapeBrushData BrushData(Bounds);

	for (const FCLandscapeToolInteractorPosition& InteractorPosition : InteractorPositions)
	{
		FIntRect SpotBounds;
		SpotBounds.Min.X = FMath::Max(FMath::FloorToInt(InteractorPosition.Position.X - TotalRadius), Bounds.Min.X);
		SpotBounds.Min.Y = FMath::Max(FMath::FloorToInt(InteractorPosition.Position.Y - TotalRadius), Bounds.Min.Y);
		SpotBounds.Max.X = FMath::Min(FMath::CeilToInt(InteractorPosition.Position.X + TotalRadius), Bounds.Max.X);
		SpotBounds.Max.Y = FMath::Min(FMath::CeilToInt(InteractorPosition.Position.Y + TotalRadius), Bounds.Max.Y);

		for (int32 Y = SpotBounds.Min.Y; Y < SpotBounds.Max.Y; Y++)
		{
			float* Scanline = BrushData.GetDataPtr(FIntPoint(0, Y));

			for (int32 X = SpotBounds.Min.X; X < SpotBounds.Max.X; X++)
			{
				float PrevAmount = Scanline[X];
				if (PrevAmount < 1.0f)
				{
					// Distance from mouse
					float MouseDist = FMath::Sqrt(FMath::Square(InteractorPosition.Position.X - (float)X) + FMath::Square(InteractorPosition.Position.Y - (float)Y));

					float PaintAmount = CalculateFalloff(MouseDist, Radius, Falloff);

					if (PaintAmount > 0.0f)
					{
						/*if (EdMode->CurrentTool && EdMode->CurrentTool->GetToolType() != ELandscapeToolType::Mask
							&& EdMode->UISettings->bUseSelectedRegion && LandscapeInfo->SelectedRegion.Num() > 0)
						{
							float MaskValue = LandscapeInfo->SelectedRegion.FindRef(FIntPoint(X, Y));

							PaintAmount *= MaskValue;
						}*/

						if (PaintAmount > PrevAmount)
						{
							// Set the brush value for this vertex
							Scanline[X] = PaintAmount;
						}
					}
				}
			}
		}
	}

	return BrushData;
}


float FCLandscapeBrushCircle_Linear::CalculateFalloff(float Distance, float Radius, float Falloff)
{
	return Distance < Radius ? 1.0f :
		Falloff > 0.0f ? FMath::Max<float>(0.0f, 1.0f - (Distance - Radius) / Falloff) :
		0.0f;
}

float FCLandscapeBrushCircle_Smooth::CalculateFalloff(float Distance, float Radius, float Falloff)
{
	float y = FCLandscapeBrushCircle_Linear::CalculateFalloff(Distance, Radius, Falloff);
	// Smooth-step it
	return y * y*(3 - 2 * y);
}