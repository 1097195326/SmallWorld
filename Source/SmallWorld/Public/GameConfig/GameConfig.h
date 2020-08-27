#pragma once


#define LandscapeObject ECC_GameTraceChannel3

#define CheckNullPtr(Ptr)  {if (Ptr == nullptr)return;}

const float FloatErrorTolerance = 0.0001f;

enum RaceEnum
{
	Race_None,
	Race_Human,
	Race_Orc,
	Race_Elf,
	Race_Undead,
	Race_Num
};

// ------------------- Building ----------------------
const int  BoundSize = 0;
const int  WorldSize = 1;
const int	CitySize = 15;
const int  CastleControllSize = 11;
const int  CastleSize = 7;
const int	CastleCenterSize = 3;
const float TitleSize = 2500.f;
const float QuarterTitleSize = TitleSize / 4.f;
const float WallSize = 625.f;


//----------------- Formation --------------------

const float Archer_FormationBoundX = 200;
const float Archer_FormationBoundY = 250;
const int32	Archer_SquareFormation_W = 10;
const int32	Archer_SquareFormation_L = 10;
const int32	Archer_HorizonalFormation_W = 20;
const int32	Archer_HorizonalFormation_L = 5;
const int32	Archer_VerticalFormation_W = 5;
const int32	Archer_VerticalFormation_L = 20;

const float Footman_FormationBoundX = 200;
const float Footman_FormationBoundY = 250;
const int32	Footman_SquareFormation_W = 10;
const int32	Footman_SquareFormation_L = 10;
const int32	Footman_HorizonalFormation_W = 20;
const int32	Footman_HorizonalFormation_L = 5;
const int32	Footman_VerticalFormation_W = 5;
const int32	Footman_VerticalFormation_L = 20;

const float Knight_FormationBoundX = 200;
const float Knight_FormationBoundY = 250;
const int32	Knight_SquareFormation_W = 10;
const int32	Knight_SquareFormation_L = 10;
const int32	Knight_HorizonalFormation_W = 20;
const int32	Knight_HorizonalFormation_L = 5;
const int32	Knight_VerticalFormation_W = 5;
const int32	Knight_VerticalFormation_L = 20;

const float Mage_FormationBoundX = 200;
const float Mage_FormationBoundY = 200;
const int32	Mage_SquareFormation_W = 5;
const int32	Mage_SquareFormation_L = 5;
const int32	Mage_HorizonalFormation_W = 25;
const int32	Mage_HorizonalFormation_L = 1;
const int32	Mage_VerticalFormation_W = 1;
const int32	Mage_VerticalFormation_L = 25;

const float Horseman_FormationBoundX = 400;
const float Horseman_FormationBoundY = 300;
const int32	Horseman_SquareFormation_W = 8;
const int32	Horseman_SquareFormation_L = 8;
const int32	Horseman_HorizonalFormation_W = 16;
const int32	Horseman_HorizonalFormation_L = 4;
const int32	Horseman_VerticalFormation_W = 4;
const int32	Horseman_VerticalFormation_L = 16;

const float SiegeEngine_FormationBoundX = 500;
const float SiegeEngine_FormationBoundY = 400;
const int32	SiegeEngine_SquareFormation_W = 5;
const int32	SiegeEngine_SquareFormation_L = 5;
const int32	SiegeEngine_HorizonalFormation_W = 25;
const int32	SiegeEngine_HorizonalFormation_L = 1;
const int32	SiegeEngine_VerticalFormation_W = 1;
const int32	SiegeEngine_VerticalFormation_L = 25;

const float Griffin_FormationBoundX = 350;
const float Griffin_FormationBoundY = 400;
const int32	Griffin_SquareFormation_W = 6;
const int32	Griffin_SquareFormation_L = 6;
const int32	Griffin_HorizonalFormation_W = 18;
const int32	Griffin_HorizonalFormation_L = 2;
const int32	Griffin_VerticalFormation_W = 2;
const int32	Griffin_VerticalFormation_L = 18;
// ----------------- Group --------------------

const int32 ArcherGroupMaxNum = Archer_SquareFormation_W * Archer_SquareFormation_L;
const int32 FootmanGroupMaxNum = Footman_SquareFormation_W * Footman_SquareFormation_L;
const int32 GriffinGroupMaxNum = Griffin_SquareFormation_W * Griffin_SquareFormation_L;
const int32 HorsemanGroupMaxNum = Horseman_SquareFormation_W * Horseman_SquareFormation_L;
const int32 KnightGroupMaxNum = Knight_SquareFormation_W * Knight_SquareFormation_L;
const int32 MageGroupMaxNum = Mage_SquareFormation_W * Mage_SquareFormation_L;
const int32 SiegeEngineGroupMaxNum = SiegeEngine_SquareFormation_W * SiegeEngine_SquareFormation_L;
									 
const int32 AllGroupMaxNum = 2;
const float GroupSize = 2500 * 3.f;


// ------------------ Soldier ---------------

const int ArcherBoundX = 200;
const int ArcherBoundY = 250;

const int FootmanBoundX = 200;
const int FootmanBoundY = 250;

const int GriffinBoundX = 350;
const int GriffinBoundY = 400;

const int HorsemanBoundX = 200;
const int HorsemanBoundY = 250;

const int KnightBoundX = 200;
const int KnightBoundY = 250;

const int MageBoundX = 200;
const int MageBoundY = 200;

const int SeigeEngineBoundX = 500;
const int SeigeEngineBoundY = 400;

const int PeasantX = 200;
const int PeasantY = 200;
