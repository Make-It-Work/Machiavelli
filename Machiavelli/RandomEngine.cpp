#include "stdafx.h"
#include "RandomEngine.h"


RandomEngine::RandomEngine()
{
}


RandomEngine::~RandomEngine()
{
}

int RandomEngine::drawCharacterCard(const std::map<int, std::unique_ptr<Character>>& map)
{
	if (!hasCharactersLeft(map)) { return -1; }
	std::random_device rd;
	std::default_random_engine e1(rd());
	std::uniform_int_distribution<int> uniform_dist(1, 8);
	int index = uniform_dist(e1);

	//return 1;
	auto it = map.find(index);
	if (it != map.end())
	{
		if (it->second->getOwner() == nullptr) {
			return index;
		}
		else {
			return drawCharacterCard(map);
		}
	}
	else {
		return -1;
	}
}

bool RandomEngine::hasCharactersLeft(const std::map<int, std::unique_ptr<Character>>& map) {
	
	for (auto iter = map.begin(); iter != map.end(); ++iter) {
		
		if (iter->second->getOwner() == nullptr) {
			return true;
		}
	}

	return false;
}
