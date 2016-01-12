#pragma once
#include <memory>
#include <vector>
#include <map>
#include "Socket.h"
#include "Player.hpp"
#include "Building.h"
#include "Character.h"
class GameHandler
{
private:
	std::vector<std::shared_ptr<Player>> players;
	std::vector<std::unique_ptr<Building>> buildingsInStore;
	
	std::map<int, std::unique_ptr<Character>> leftOverCharacters;

	void initCharacterCards();

	std::shared_ptr<Player> stock;

public:
	GameHandler();
	~GameHandler();
	int getAmountOfPlayers() { return players.size(); }
	std::map<int, std::unique_ptr<Character>> characters;

	//Init functions
	std::shared_ptr<Player> getOldestPlayer();
	std::shared_ptr<Player> addPlayer(std::shared_ptr<Socket> socket);

	//CharacterCard functions
	int getAmountOfCharacters() {
		int counter = 0;
		/*for each (const auto& kv in characters)
		{
			if (kv.second->getOwner() == nullptr) {
				counter++;
			}
		}*/
		return counter;
	}
	void layOffCharacterCard(int cardId);
	void pickCharacterCard(int cardId, std::shared_ptr<Player> player);

	std::shared_ptr<Player> getNextPlayer(std::shared_ptr<Player> currentPlayer);
		
};

