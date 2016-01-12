#pragma once
#include <random>
#include <vector>
#include <algorithm>
#include <memory>
#include <map>
#include <chrono>
#include "Character.h"

class RandomEngine
{
private:
	

public:
	RandomEngine();
	~RandomEngine();

	static int drawCharacterCard(const std::map<int, std::unique_ptr<Character>>& characters);
	static bool hasCharactersLeft(const std::map<int, std::unique_ptr<Character>>& map);
};

