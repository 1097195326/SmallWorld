#include "STextButton.h"



void STextButton::Construct(const FArguments & InArgs)
{
	float Width = InArgs._Width;

	ChildSlot
		[
			SNew(SBox)
		];

}
STextButton::~STextButton()
{

}