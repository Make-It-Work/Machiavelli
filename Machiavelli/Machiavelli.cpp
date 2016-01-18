//
//  main.cpp
//  socketexample
//
//  Created by Bob Polis on 16/09/14.
//  Copyright (c) 2014 Avans Hogeschool, 's-Hertogenbosch. All rights reserved.
//
#include "stdafx.h"

#include <thread>
#include <iostream>
#include <exception>
#include <memory>
#include <utility>
using namespace std;

#include "Socket.h"
#include "Sync_queue.h"
#include "ClientCommand.h"
#include "GameHandler.h"
#include "Player.hpp"
#include "RandomEngine.h"

namespace machiavelli {
	const int tcp_port{ 1080 };
	const string prompt{ "machiavelli> " };
}

bool turnfinished = true;

static Sync_queue<ClientCommand> queue;
GameHandler theGame;
std::string stateOfGame = "PlayersConnecting";
std::shared_ptr<Player> currentPlayer = nullptr;

void consume_command() // runs in its own thread
{
	try {
		while (true) {
			ClientCommand command{ queue.get() }; // will block here unless there are still command objects in the queue
			shared_ptr<Socket> client{ command.get_client() };
			shared_ptr<Player> player{ command.get_player() };
			try {
				while (!turnfinished) {

				}
				turnfinished = false;
				if (stateOfGame == "CharacterCards") {

					std::string s_pickedCard = command.get_cmd();
					if (std::stoi(s_pickedCard) != NULL) {
						player->get_socket()->write("you picked " + s_pickedCard + "\r\n");
						theGame.pickCharacterCard(std::stoi(s_pickedCard), player);
						currentPlayer = theGame.getNextPlayer(player);
					}
					else {
						player->get_socket()->write("Something went wrong, please pick one of the numbers: \r\n");
						player->get_socket()->write(machiavelli::prompt);
					}
				}
				else if (stateOfGame == "TurnState")
				{
					if (player == currentPlayer)
					{

					}
				}
				else {
					// TODO handle command here
					*client << player->get_name() << ", you wrote: '" << command.get_cmd() << "', but I'll ignore that for now.\r\n" << machiavelli::prompt;
				}
			}
			catch (const exception& ex) {
				cerr << "*** exception in consumer thread for player " << player->get_name() << ": " << ex.what() << '\n';
				if (client->is_open()) {
					client->write("Sorry, something went wrong during handling of your request.\r\n");
				}
			}
			catch (...) {
				cerr << "*** exception in consumer thread for player " << player->get_name() << '\n';
				if (client->is_open()) {
					client->write("Sorry, something went wrong during handling of your request.\r\n");
				}
			}
			turnfinished = true;
		}
	}
	catch (...) {
		cerr << "consume_command crashed\n";
	}
}

void handle_client(shared_ptr<Socket> client) // this function runs in a separate thread
{
	try {
		client->write("Welcome to Server 1.0! To quit, type 'quit'.\r\n");
		std::shared_ptr<Player> player = theGame.addPlayer(client);

		while (true) { // game loop
			try {
				if (theGame.getAmountOfPlayers() == 2 && stateOfGame == "PlayersConnecting") {
					stateOfGame = "CharacterCards";
				}
				if (currentPlayer == nullptr && theGame.getAmountOfPlayers() == 2) {
					currentPlayer = theGame.getOldestPlayer();
					theGame.divideGold();
					theGame.divideBuilding();
				} 
				while (!turnfinished) {

				}
				if (stateOfGame == "CharacterCards") {
					std::this_thread::sleep_for(std::chrono::milliseconds(10));
					int cardId = RandomEngine::drawCharacterCard(theGame.characters);
					if (cardId == -1) {
						stateOfGame = "TurnState";
						currentPlayer = theGame.nextTurn();
					}
					else {
						currentPlayer->get_socket()->write("De bovenste kaart was de " +
							theGame.characters[cardId]->getName() +
							". Kies een van de onderstaande kaarten:"
							);
						theGame.layOffCharacterCard(cardId);
						for (auto const& character : theGame.characters) {
							if (character.second->getOwner() == nullptr) {
								currentPlayer->get_socket()->write("\r\n");
								currentPlayer->get_socket()->write(std::to_string(character.second->getId()));
								currentPlayer->get_socket()->write(" " + character.second->getName());
							}
						}
						currentPlayer->get_socket()->write("\r\n" + machiavelli::prompt);
					}
				}
				if (stateOfGame == "TurnState")
				{
					cout << "Starting turn state";
					if (currentPlayer == theGame.getStock())
						continue;
					theGame.printTurn(currentPlayer);

				}
				
				// read first line of request
				string cmd{ client->readline() };
				cerr << '[' << client->get_dotted_ip() << " (" << client->get_socket() << ") " << player->get_name() << "] " << cmd << "\r\n";

				if (cmd == "quit") {
					client->write("Bye!\r\n");
					break; // out of game loop, will end this thread and close connection
				}
				else if (cmd == "status") {
					theGame.showGameStatus(client);
				}
				else if (cmd == "help") {
					theGame.showHelp(client);
				}

				ClientCommand command{ cmd, client, player };
				queue.put(command);


			}
			catch (const exception& ex) {
				*client << "ERROR: " << ex.what() << "\r\n";
			}
			catch (...) {
				client->write("ERROR: something went wrong during handling of your request. Sorry!\r\n");
			}
		}
		client->close();
	}
	catch (...) {
		cerr << "handle_client crashed\n";
	}
}

int main(int argc, const char * argv[])
{
	// start command consumer thread
	thread consumer{ consume_command };

	// create a server socket
	ServerSocket server{ machiavelli::tcp_port };

	while (true) {
		try {
			while (true) {
				// wait for connection from client; will create new socket
				cerr << "server listening" << '\n';
				unique_ptr<Socket> client{ server.accept() };

				// communicate with client over new socket in separate thread
				thread handler{ handle_client, move(client) };
				handler.detach(); // detaching is usually ugly, but in this case the right thing to do
			}
		}
		catch (const exception& ex) {
			cerr << ex.what() << ", resuming..." << '\n';
		}
		catch (...) {
			cerr << "problems, problems, but: keep calm and carry on!\n";
		}
	}
	consumer.join();
	return 0;
}
