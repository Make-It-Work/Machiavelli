#include "stdafx.h"
#include "CharacterFactory.h"
#include "Moordenaar.h"
#include "Dief.h"
#include "Magier.h"
#include "Koning.h"
#include "Prediker.h"
#include "Koopman.h"
#include "Bouwmeester.h"
#include "Condottiere.h"

std::map<std::string, std::function<std::unique_ptr<Character>()>> CharacterFactory::factory;

CharacterFactory::CharacterFactory()
{
	factory.emplace("Moordenaar", []() -> std::unique_ptr<Character> {
		return std::unique_ptr<Character>(new Moordenaar);
	});
	factory.emplace("Dief", []() -> std::unique_ptr<Character> {
		return std::unique_ptr<Character>(new Dief);
	});
	factory.emplace("Magier", []() -> std::unique_ptr<Character> {
		return std::unique_ptr<Character>(new Magier);
	});
	factory.emplace("Koning", []() -> std::unique_ptr<Character> {
		return std::unique_ptr<Character>(new Koning);
	});
	factory.emplace("Prediker", []() -> std::unique_ptr<Character> {
		return std::unique_ptr<Character>(new Prediker);
	});
	factory.emplace("Koopman", []() -> std::unique_ptr<Character> {
		return std::unique_ptr<Character>(new Koopman);
	});
	factory.emplace("Bouwmeester", []() -> std::unique_ptr<Character> {
		return std::unique_ptr<Character>(new Bouwmeester);
	});
	factory.emplace("Condottiere", []() -> std::unique_ptr<Character> {
		return std::unique_ptr<Character>(new Condottiere);
	});
}


CharacterFactory::~CharacterFactory()
{
}

std::unique_ptr<Character> CharacterFactory::createCharacter(std::string s) {
	std::string delimiter = ";";
	size_t pos = 0;
	std::string token;
	pos = s.find(delimiter);
	int id = std::stoi(s.substr(0, pos));
	std::string name = s.substr(pos + 1);

	auto it = factory.find(name);
	if (it != factory.end()) {
		std::function<std::unique_ptr<Character>()> execute = it->second;
		return execute();
	}
	else {
		std::cerr << "key '" << name << "' not found" << '\n';
	}
}