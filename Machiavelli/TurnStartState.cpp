#include "stdafx.h"
#include "TurnStartState.h"
#include "Character.h"

TurnStartState::TurnStartState(GameHandler gh)
{
	game = gh;
}


TurnStartState::~TurnStartState()
{
}

void TurnStartState::print(std::shared_ptr<Player> player)
{
	Character& chr = game.getCharacter(game.getTurnID());
	player->get_socket()->write("Je bent nu de: " + chr.getName() + "\r\n");
	player->get_socket()->write("Goud: " + std::to_string(player->getGold()) + "\r\n");
	player->get_socket()->write("\r\nGebouwen: \r\n");
	game.printBuildings(player, true);
	player->get_socket()->write("\r\nHandkaarten: \r\n");
	game.printBuildings(player, false);
	player->get_socket()->write("\r\nMaak een keuze: \r\n");
	player->get_socket()->write("[0] Bekijk het goud en gebouwen van de tegenstander (en maak dan een keuze) \r\n");
	player->get_socket()->write("[1] Neem 2 goudstukken \r\n");
	player->get_socket()->write("[2] Neem 2 bouwkaarten en leg er 1 af \r\n");
	player->get_socket()->write("[3] Maak gebruik van de karaktereigenschap van de " + chr.getName() + " \r\n");
}

void TurnStartState::handleCommand(ClientCommand command)
{

}

std::shared_ptr<TurnState> TurnStartState::nextState()
{

}