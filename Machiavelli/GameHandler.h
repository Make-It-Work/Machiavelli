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

class GameHandler : public std::enable_shared_from_this<GameHandler>
{
private:
	std::vector<std::shared_ptr<Player>> players;
	std::map<int, std::unique_ptr<Character>> leftOverCharacters;
	std::shared_ptr<Player> stock;
	std::map<int, std::unique_ptr<Building>> buildings;

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

	bool addGold(std::shared_ptr<Player>, int gold);
	int amountOfGoldPieces(std::shared_ptr<Player> player);

	void divideBuilding();

	void getBuilding(std::shared_ptr<Player> player);

	//turn functions
	void printTurn(std::shared_ptr<Player> player);
	std::shared_ptr<Player> startTurns();
	int getTurnID() { return turnID; };
	void printBuildings(std::shared_ptr<Player> player, bool built);
	void handleCommand(ClientCommand command);
	void changeTurnState(std::shared_ptr<TurnState> state) { turn = state; };
	std::vector<int> drawBuildingCards(int nCards);
	std::string getBuildingString(int id) { return buildings[id]->getName() + "(" + std::to_string(buildings[id]->getPoints()) + "," + buildings[id]->getColor() + ")"; };
	void assignBuilding(int id, std::shared_ptr<Player> player);

	//Turn Actions
	std::string buildBuilding(std::shared_ptr<Player>player, int buildingId);

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

