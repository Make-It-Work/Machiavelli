#include "stdafx.h"
#include "Goldpiece.h"


Goldpiece::Goldpiece(std::shared_ptr<Player> stock)
{
	owner = stock;
}


Goldpiece::~Goldpiece()
{
}
