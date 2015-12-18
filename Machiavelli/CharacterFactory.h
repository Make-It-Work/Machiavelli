#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <functional>
#include <memory>
#include "Character.h"
class CharacterFactory
{
public:
	CharacterFactory();
	~CharacterFactory();

	static std::unique_ptr<Character> createCharacter(std::string name);
private:
	static std::map<std::string, std::function<std::unique_ptr<Character>()>> factory;
};

