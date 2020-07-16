#pragma once


template<class ClassType>
class  SingleTemplateClass
{
public:
	static ClassType * GetInstance()
	{
		static ClassType Instance;
		return &Instance;
	}
};