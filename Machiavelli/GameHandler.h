#pragma once
#include <memory>
#include <vector>
#include <map>
#include "Socket.h"
#include "Player.hpp"
#include "Building.h"
#include "Character.h"
#include "Goldpiece.h"
#include "TurnState.h"

class GameHandler
{
private:
	std::vector<std::shared_ptr<Player>> players;
	std::vector<std::unique_ptr<Building>> buildingsInStore;
	std::map<int, std::unique_ptr<Character>> leftOverCharacters;
	std::shared_ptr<Player> stock;
	std::vector<std::unique_ptr<Building>> buildings;

	std::shared_ptr<TurnState> turn = nullptr;

	int goldLeft = 32;
	
	void initCharacterCards();
	void initBuildingCards();
	
	//turn data
	int turnID = -1;
public:
	GameHandler();
	~GameHandler();
	int getAmountOfPlayers() { return players.size(); }
	std::map<int, std::unique_ptr<Character>> characters;

	//Init functions
	std::shared_ptr<Player> getOldestPlayer();
	std::shared_ptr<Player> addPlayer(std::shared_ptr<Socket> socket);
	void divideGold();

	void addGold(std::shared_ptr<Player>, int gold);
	int amountOfGoldPieces(std::shared_ptr<Player> player);

	void divideBuilding();

	void getBuilding(std::shared_ptr<Player> player);

	//turn functions
	void printTurn(std::shared_ptr<Player> player);
	std::shared_ptr<Player> nextTurn();
	int getTurnID() { return turnID; };
	void printBuildings(std::shared_ptr<Player> player, bool built);

	//CharacterCard functions
	int amountOfCharactersLeft();
	void layOffCharacterCard(int cardId);
	void pickCharacterCard(int cardId, std::shared_ptr<Player> player);
	Character& getCharacter(int cardId) { return *characters[cardId].get(); };

	//Helper functions
	std::shared_ptr<Player> getNextPlayer(std::shared_ptr<Player> currentPlayer);
	void showGameStatus(std::shared_ptr<Socket> s);
	std::string buildingsForPlayer(std::shared_ptr<Player> player);
	void showHelp(std::shared_ptr<Socket> client);
	std::shared_ptr<Player> getStock() { return stock; };
		
};

