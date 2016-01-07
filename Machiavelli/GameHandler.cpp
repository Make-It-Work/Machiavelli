#include "stdafx.h"
#include "GameHandler.h"
#include "Player.hpp"
#include <fstream>
#include <sstream>
#include <iterator>
#include <string>
#include "CharacterFactory.h"
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

	if (players.size() == 2) {
		startGame();
	}

	return player;
}

void GameHandler::startGame() {
	std::shared_ptr<Player> firstplayer;
	for (std::shared_ptr<Player> player : players) {
		if (firstplayer == nullptr) {
			firstplayer = player;
		}
		else if (firstplayer->get_age() < player->get_age()) {
			firstplayer = player;
		}
	}

	for (std::shared_ptr<Player> player : players) {
		player->get_socket()->write("Let's start the game, " + firstplayer->get_name() + " may start.\r\n");
		if (player == firstplayer) {
			dealCharacterCards(player);
		}
	}
}

void GameHandler::initCharacterCards() {
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
			std::unique_ptr<Character> c = CharacterFactory::createCharacter(s);
			characters.emplace(c->getId(), std::move(c));
		}
	}
}

void GameHandler::dealCharacterCards(std::shared_ptr<Player> firstPlayer) {
	int cardId = RandomEngine::drawCharacterCard();

	firstPlayer->get_socket()->write("De bovenste kaart was de " + characters[cardId]->getName() + ". Kies een van de onderstaande kaarten:");
	leftOverCharacters[cardId] = std::move(characters[cardId]);
	for (auto const &character : characters) {
		if (character.second.get() != nullptr) {
			firstPlayer->get_socket()->write("\r\n");
			firstPlayer->get_socket()->write(std::to_string(character.second->getId()));
			firstPlayer->get_socket()->write(" " + character.second->getName());
		}
	}

}
