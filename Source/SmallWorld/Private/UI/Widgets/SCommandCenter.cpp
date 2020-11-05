#include "SCommandCenter.h"
#include "GameDataManager.h"
#include "SHGameActorIcon.h"
#include "CommandCenterDataClass.h"
#include "GameStyle.h"
#include "Kismet/KismetMathLibrary.h"
#include "GroundTileActor.h"
#include "CastleTileActor.h"

void SCommandCenter::Construct(const FArguments & InArgs)
{
	CommandCenterData = InArgs._CommandCenterData;

	TSharedPtr<SVerticalBox> ItemList;
	ChildSlot.Padding(24, 0, 0, 0)
		.VAlign(VAlign_Bottom)
		.HAlign(HAlign_Left)
		[
			SAssignNew(ItemList, SVerticalBox)
		];
	ItemList->AddSlot()
		.HAlign(HAlign_Left)
		.VAlign(VAlign_Center)
		.AutoHeight()
		[
			SNew(SButton)
			.ButtonStyle(&FGameStyle::Get().GetWidgetStyle<FButtonStyle>("MainView.Button.Move"))
			.OnClicked(this, &SCommandCenter::OnButtonClicked,1)
		];
}
void SCommandCenter::RefreshView()
{


}
FReply SCommandCenter::OnButtonClicked(int32 InIndex)
{
	switch (InIndex)
	{
	case 1:
	{
		TArray<AGroundTileActor*>  TileArray = CommandCenterData->BuildingActor->GetCastleTileActor()->AroundActorArray;
		int32 TileIndex = UKismetMathLibrary::RandomInteger(TileArray.Num());
		FVector SpLocation = FVector::ZeroVector;
		AGroundTileActor * GroundTile = TileArray[TileIndex];
		if (GroundTile->GetSoldiers().Num() > 0)
		{
			for (auto IterTile : TileArray)
			{
				if (IterTile->GetSoldiers().Num() == 0)
				{
					SpLocation = IterTile->GetActorLocation();
					GroundTile = IterTile;
					break;
				}
			}
		}
		else
		{
			SpLocation = GroundTile->GetActorLocation();
		}
		if (SpLocation != FVector::ZeroVector)
		{
			SoldierTypeEnum SoldierType = (SoldierTypeEnum)UKismetMathLibrary::RandomIntegerInRange(Soldier_Archer, Soldier_SiegeEngine);

			ASoldierPawn * SoldierPawn = CommandCenterData->SpawnSoldier(SoldierType);
			if (SoldierPawn)
			{
				SoldierPawn->SetActorLocationAndRotation(SpLocation, CommandCenterData->BuildingActor->GetActorRotation());
				GroundTile->AddSoldier(SoldierPawn);
				SoldierPawn->SetGroundTile(GroundTile);
			}
		}
		break;
	}
	}
	return FReply::Handled();
}