#pragma once

template <typename T>
class c_singleton
{
public:
	static T* get( )
	{
		static T _inst = T( );
		return &_inst;
	}
};