#pragma once


template<class ClassType>
class  SingleTemplate
{
public:
	static ClassType * GetInstance()
	{
		static ClassType Instance;
		return &Instance;
	}
};