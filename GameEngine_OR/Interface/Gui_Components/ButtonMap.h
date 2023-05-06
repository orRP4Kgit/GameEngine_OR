#pragma once
#include "../../Core/Engine.h"

class Button;

class ButtonMap 
{
public:
	static std::map<std::string, Button*>& GetMap();
};

