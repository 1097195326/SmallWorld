#pragma once


template<class ClassType>
class GAMEFRAME_API SingleTemplate
{
public:
	ClassType * GetInstance()
	{
		static ClassType Instance;
		return &Instance;
	}
};