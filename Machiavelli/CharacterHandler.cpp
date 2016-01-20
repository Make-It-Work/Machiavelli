#include "stdafx.h"
#include "CharacterHandler.h"
#include "CharacterFactory.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iterator>
#include "Player.hpp"

CharacterHandler::CharacterHandler(std::shared_ptr<Player> s)
{
	stock = s;
}


CharacterHandler::~CharacterHandler()
{
	initCharacterCards();
}

void CharacterHandler::initCharacterCards() {
	std::unique_ptr<CharacterFactory> charF = std::unique_ptr<CharacterFactory>(new CharacterFactory);
	const std::string textfile{ "karakterkaarten.csv" };
	std::ifstream input_file{ textfile };
	std::string line;

	while (std::getline(input_file, line)) {

		std::istringstream buf(line);
		std::istream_iterator <std::string> beg(buf), end;
		std::vector<std::string> line(beg, end);
		for each(std::string s in line) {
			std::unique_ptr<Character> c = charF->createCharacter(s);
			characters.emplace(c->getId(), std::move(c));
		}
	}
}

const Character& CharacterHandler::getCharacterRef(int id) {
	return *characters[id];
}

void CharacterHandler::layOffCharacterCard(int cardId) {
	if (amountOfCharactersLeft() % 2 == 0) {
		characters[cardId]->setOwner(stock);
	}
}


int CharacterHandler::amountOfCharactersLeft() {
	int counter = 0;
	for each (const auto& kv in characters)
	{
		if (kv.second->getOwner() == nullptr) {
			counter++;
		}
	}
	return counter;

}

void CharacterHandler::pickCharacterCard(int cardId, std::shared_ptr<Player> player) {
	characters[cardId]->setOwner(player);
}


std::shared_ptr<Player> CharacterHandler::getCardOwner(int cardId)
{
	return characters[cardId]->getOwner();
}