#include "LandscapePaintTools.h"



void FCLandscapeToolStrokePaint::Apply(FCLandscapeBrush* Brush, const TArray<FCLandscapeToolInteractorPosition>& InteractorPositions)
{
	// Invert when holding Shift
	//UE_LOG(LogLandscape, Log, TEXT("bInvert = %d"), bInvert);
	bool bInvert = InteractorPositions.Last().bModifierPressed;

	// Get list of verts to update
	FCLandscapeBrushData BrushInfo = Brush->ApplyBrush(InteractorPositions);
	if (!BrushInfo)
	{
		return;
	}

	int32 X1, Y1, X2, Y2;
	BrushInfo.GetInclusiveBounds(X1, Y1, X2, Y2);

	// Tablet pressure
	float Pressure = 1.0f;

	this->Cache.CacheData(X1, Y1, X2, Y2);

	bool bUseWeightTargetValue = false;

	// The data we'll be writing to
	TArray<ToolTarget::CacheClass::DataType> Data;
	this->Cache.GetCachedData(X1, Y1, X2, Y2, Data);

	// The source data we use for editing. 
	TArray<ToolTarget::CacheClass::DataType>* SourceDataArrayPtr = &Data;
	TArray<ToolTarget::CacheClass::DataType> OriginalData;

	if (!bUseWeightTargetValue)
	{
		// When painting weights (and not using target value mode), we use a source value that tends more
		// to the current value as we paint over the same region multiple times.
		// TODO: Make this frame-rate independent
		this->Cache.GetOriginalData(X1, Y1, X2, Y2, OriginalData);
		SourceDataArrayPtr = &OriginalData;

		for (int32 Y = Y1; Y < Y2; Y++)
		{
			auto* DataScanline = Data.GetData() + (Y - Y1) * (X2 - X1 + 1) + (0 - X1);
			auto* OriginalDataScanline = OriginalData.GetData() + (Y - Y1) * (X2 - X1 + 1) + (0 - X1);
			for (int32 X = X1; X < X2; X++)
			{
				float VertexInfluence = TotalInfluenceMap.FindRef(FIntPoint(X, Y));

				auto& CurrentValue = DataScanline[X];
				auto& SourceValue = OriginalDataScanline[X];

				SourceValue = FMath::Lerp(SourceValue, CurrentValue, FMath::Min<float>(VertexInfluence * 0.05f, 1.0f));
			}
		}
	}

	// Adjust strength based on brush size and drawscale, so strength 1 = one hemisphere
	const float AdjustedStrength = 255.f;// ToolTarget::StrengthMultiplier(this->LandscapeInfo, 100.f);
	FCWeightmapToolTarget::CacheClass::DataType DestValue = FCWeightmapToolTarget::CacheClass::ClampValue(255.0f * 1);

	float PaintStrength = 0.3f * Pressure * AdjustedStrength;

	// TODO: make paint tool framerate independent like the sculpt tool
	// const float DeltaTime = FMath::Min<float>(FApp::GetDeltaTime(), 0.1f); // Under 10 fps slow down paint speed
	// SculptStrength *= DeltaTime * 3.0f; // * 3.0f to partially compensate for impact of DeltaTime on slowing the tools down compared to the old framerate-dependent version

	if (PaintStrength <= 0.0f)
	{
		return;
	}

	if (!bUseWeightTargetValue)
	{
		PaintStrength = FMath::Max(PaintStrength, 1.0f);
	}

	// Apply the brush
	for (int32 Y = BrushInfo.GetBounds().Min.Y; Y < BrushInfo.GetBounds().Max.Y; Y++)
	{
		const float* BrushScanline = BrushInfo.GetDataPtr(FIntPoint(0, Y));
		auto* DataScanline = Data.GetData() + (Y - Y1) * (X2 - X1 + 1) + (0 - X1);
		auto* SourceDataScanline = SourceDataArrayPtr->GetData() + (Y - Y1) * (X2 - X1 + 1) + (0 - X1);

		for (int32 X = BrushInfo.GetBounds().Min.X; X < BrushInfo.GetBounds().Max.X; X++)
		{
			const FIntPoint Key = FIntPoint(X, Y);
			const float BrushValue = BrushScanline[X];

			// Update influence map
			float VertexInfluence = TotalInfluenceMap.FindRef(Key);
			TotalInfluenceMap.Add(Key, VertexInfluence + BrushValue);

			float PaintAmount = BrushValue * PaintStrength;
			auto& CurrentValue = DataScanline[X];
			const auto& SourceValue = SourceDataScanline[X];

			if (bUseWeightTargetValue)
			{
				CurrentValue = FMath::Lerp(CurrentValue, DestValue, PaintAmount / AdjustedStrength);
			}
			else
			{
				if (bInvert)
				{
					CurrentValue = ToolTarget::CacheClass::ClampValue(FMath::Min<int32>(SourceValue - FMath::RoundToInt(PaintAmount), CurrentValue));
				}
				else
				{
					CurrentValue = ToolTarget::CacheClass::ClampValue(FMath::Max<int32>(SourceValue + FMath::RoundToInt(PaintAmount), CurrentValue));
				}
			}
		}
	}

	/*ALandscape* Landscape = LandscapeInfo->LandscapeActor.Get();

	if (Landscape != nullptr && Landscape->HasProceduralContent && !GetMutableDefault<UEditorExperimentalSettings>()->bProceduralLandscape)
	{
		FMessageLog("MapCheck").Warning()->AddToken(FTextToken::Create(LOCTEXT("LandscapeProcedural_ChangingDataWithoutSettings", "This map contains landscape procedural content, modifying the landscape data will result in data loss when the map is reopened with Landscape Procedural settings on. Please enable Landscape Procedural settings before modifying the data.")));
		FMessageLog("MapCheck").Open(EMessageSeverity::Warning);
	}*/

	this->Cache.SetCachedData(X1, Y1, X2, Y2, Data);
	this->Cache.Flush();
}