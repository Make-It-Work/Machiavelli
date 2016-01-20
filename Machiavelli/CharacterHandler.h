#pragma once
#include <memory>
#include <map>

class Player;
class Character;
class CharacterHandler
{
public:
	CharacterHandler(std::shared_ptr<Player> s);
	~CharacterHandler();

	void initCharacterCards();
	const Character& getCharacterRef(int id);

	void layOffCharacterCard(int cardId);
	int amountOfCharactersLeft();
	void pickCharacterCard(int cardId, std::shared_ptr<Player> player);
	std::shared_ptr<Player> getCardOwner(int cardId);

	typedef std::map<int, std::unique_ptr<Character>> character_map;
	const character_map & getCharacters() const { return characters; }

private:
	std::map<int, std::unique_ptr<Character>> characters;
	std::shared_ptr<Player> stock;
};

