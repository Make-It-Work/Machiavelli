#include "stdafx.h"
#include "GameHandler.h"
#include "Player.hpp"
#include <fstream>
#include <sstream>
#include <iterator>
#include <string>
#include <algorithm>
#include "CharacterFactory.h"
#include "BuildingFactory.h"
#include "RandomEngine.h"

namespace machiavelli {
	const int tcp_port{ 1080 };
	const std::string prompt{ "machiavelli> " };
}

GameHandler::GameHandler()
{
	stock = std::make_shared<Player>();
	stock->set_name("stock");
	initCharacterCards();
	initBuildingCards();
}


GameHandler::~GameHandler()
{
}

std::shared_ptr<Player> GameHandler::addPlayer(std::shared_ptr<Socket> socket)
{
	socket->write("What's your name?\r\n");
	socket->write(machiavelli::prompt);
	std::string name{ socket->readline() };
	socket->write("What's your age?\r\n");
	socket->write(machiavelli::prompt);
	int age{ std::stoi(socket->readline()) };
	std::shared_ptr<Player> player{ new Player{ name, age } };
	*socket << "Welcome, " << name << ", have fun playing our game!\r\n";
	player->set_socket(socket);
	players.push_back(player);

	return player;
}

std::shared_ptr<Player> GameHandler::getOldestPlayer() {
	std::shared_ptr<Player> firstplayer;
	for (std::shared_ptr<Player> player : players) {
		if (firstplayer == nullptr) {
			firstplayer = player;
		}
		else if (player->get_age() > firstplayer->get_age()) {
			firstplayer = player;
		}
	}
	return firstplayer;
}

void GameHandler::initCharacterCards() {
	std::unique_ptr<CharacterFactory> charF = std::unique_ptr<CharacterFactory>(new CharacterFactory);
	const std::string textfile{ "karakterkaarten.csv" };
	std::ifstream input_file{ textfile }; // stack-based file object; deze constructie opent de file voor lezen
	std::string line;

	// getline() leest een regel die eindigt in een \n
	// (je kunt ook een 3e param meegeven als je een ander 'regeleinde' wil gebruiken)
	while (std::getline(input_file, line)) { // getline() geeft false zodra end-of-file is bereikt
		
		std::istringstream buf(line);
		std::istream_iterator <std::string> beg(buf), end;
		std::vector<std::string> line(beg, end);
		for each(std::string s in line) {
			std::unique_ptr<Character> c = charF->createCharacter(s);
			characters.emplace(c->getId(), std::move(c));
		}
	}
}

void GameHandler::initBuildingCards() {
	std::unique_ptr<BuildingFactory> charF = std::unique_ptr<BuildingFactory>(new BuildingFactory);
	const std::string textfile{ "Bouwkaarten.csv" };
	std::ifstream input_file{ textfile }; // stack-based file object; deze constructie opent de file voor lezen
	std::string line;

	// getline() leest een regel die eindigt in een \n
	// (je kunt ook een 3e param meegeven als je een ander 'regeleinde' wil gebruiken)
	while (std::getline(input_file, line)) { // getline() geeft false zodra end-of-file is bereikt

		std::istringstream buf(line);
		std::istream_iterator <std::string> beg(buf), end;
		std::vector<std::string> line(beg, end);
		std::unique_ptr<Building> c = charF->createBuilding(line[0]);
		buildings.push_back(std::move(c));
	}
}

void GameHandler::divideGold()
{
	std::cout << "dividing gold motherfucker \r\n";
	for (auto const& player : players) {
		addGold(player, 2);
	}
}

void GameHandler::addGold(std::shared_ptr<Player> playerm, int gold) {
	if (goldLeft > gold)
	{
		playerm->addGold(gold);
		goldLeft -= gold;
	}
}

int GameHandler::amountOfGoldPieces(std::shared_ptr<Player> player) {
	return player->getGold();
}


void GameHandler::divideBuilding() {
	for (auto const& player : players) {
		for (int i = 0; i < 4; i++) {
			getBuilding(player);
		}
	}
}

void GameHandler::getBuilding(std::shared_ptr<Player> player) {
	int cardId = RandomEngine::drawBuildingCard(buildings);
	buildings[cardId]->setOwner(player);
}

void GameHandler::layOffCharacterCard(int cardId) {
	if (amountOfCharactersLeft() % 2 == 0) {
		characters[cardId]->setOwner(stock);
	}
}

int GameHandler::amountOfCharactersLeft() {
	int counter = 0;
	for each (const auto& kv in characters)
	{
		if (kv.second->getOwner() == nullptr) {
			counter++;
		}
	}
	return counter;
	
}

void GameHandler::pickCharacterCard(int cardId, std::shared_ptr<Player> player) {
	characters[cardId]->setOwner(player);
}

std::shared_ptr<Player> GameHandler::getNextPlayer(std::shared_ptr<Player> currentPlayer) {
	//CHANGE THIS
	auto i = std::find(players.begin(), players.end(), currentPlayer);
	int nPosition;
	if (i + 1 != players.end())
	{
		nPosition = distance(players.begin(), i) + 1;
	}
	else {
		nPosition = 0;
	}

	std::cout << " next player at position: " << nPosition << std::endl;

	return players[nPosition];
}

void GameHandler::showGameStatus(std::shared_ptr<Socket> s) {
	s->write("Player one: " + players[0]->get_name() + "\r\n");
	s->write("Goldpieces: " + std::to_string(amountOfGoldPieces(players[0])) + " \r\n");
	s->write("Buildings: " + buildingsForPlayer(players[0]) + "\r\n");

	s->write("The bank holds: \r\n");
	s->write("Goldpieces: " + std::to_string(amountOfGoldPieces(stock)) + "\r\n");
	//s->write("Buildings")

	s->write("Player two: " + players[1]->get_name() + "\r\n");
	s->write("Goldpieces: " + std::to_string(amountOfGoldPieces(players[1])) + " \r\n");
	s->write("Buildings: " + buildingsForPlayer(players[1]) + "\r\n");
	s->write(machiavelli::prompt);
}

std::string GameHandler::buildingsForPlayer(std::shared_ptr<Player> player) {
	std::string s = "";
	int counter = 0;
	for (const auto& building : buildings) {
		if (building->getOwner() == player && building->isPlayed()) {
			s += building->getName() + " ";
			counter++;
		}
	}
	s = std::to_string(counter) + s;
	return s;
}

void GameHandler::showHelp(std::shared_ptr<Socket> client) {
	client->write("In een beurt kun je: \r\n");
	client->write("1 - 2 goudstukken innen \r\n");
	client->write("2 - 2 gebouwen van de stapel nemen en er 1 terugleggen \r\n");
	client->write("3 - Een gebouw bouwen \r\n");
	client->write("4 - Je karakteractie uitvoeren \r\n");
	client->write("Karakteracties zijn: \r\n");
	client->write("1 - Moordenaar - Een karakter vermoorden \r\n");
	client->write("2 - Dief - Van een andere speler stelen \r\n");
	client->write("3 - Magiër - Bouwkaarten omruilen \r\n");
	client->write("4 - Koning - De volgende ronde beginnen en geld verdienen voor gele gebouwen \r\n");
	client->write("5 - Prediker - Immuun tegen Condotierre en geld verdienen voor blauwe gebouwen \r\n");
	client->write("6 - Koopman - Extra goudstuk krijgen en geld verdienen voor groene gebouwen \r\n");
	client->write("7 - Bouwmeester - Twee extra bouwkaarten pakken en drie gebouwen bouwen \r\n");
	client->write("8 - Condotierre - Gebouw vernietigen en geld verdienen voor rode gebouwen \r\n");
}

std::shared_ptr<Player> GameHandler::nextTurn() {
	for each (const auto& kv in characters)
	{
		if (kv.second->getOwner() != nullptr) {
			turnID = kv.first;
			return kv.second->getOwner();
		}
	}
	return stock;
}

void GameHandler::printAvailableBuildings(std::shared_ptr<Player> player) {
	for (const auto& building : buildings) {
		if (building->getOwner() == player && !building->isPlayed()) {
			player->get_socket()->write(building->getName() + "( " + building->getColor() + ", " + std::to_string(building->getCost()) + ")\r\n");
		}
	}
}