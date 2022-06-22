#pragma once
#pragma once
#include "../memory/singleton.h"
#include "../../common.h"

class c_key_handler : public c_singleton<c_key_handler>
{
public:
	bool auto_check( int key, int style );
};