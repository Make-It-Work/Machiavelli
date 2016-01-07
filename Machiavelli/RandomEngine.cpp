#include "stdafx.h"
#include "RandomEngine.h"


RandomEngine::RandomEngine()
{
}


RandomEngine::~RandomEngine()
{
}

int RandomEngine::drawCharacterCard()
{
	std::random_device rd;
	std::default_random_engine e1(rd());
	std::uniform_int_distribution<int> uniform_dist(1, 8);
	return uniform_dist(e1);
}
