#include "stdafx.h"
#include "TurnStartState.h"
#include "Character.h"
#include "TurnBuildingCardState.h"
#include "TurnBuildingActionState.h"
//TurnStartState::TurnStartState(GameHandler& gh)
TurnStartState::TurnStartState(std::shared_ptr<GameHandler> gameHandler)
{
	game = gameHandler;
}


TurnStartState::~TurnStartState()
{
}

void TurnStartState::print(std::shared_ptr<Player> player)
{
	//Character& chr = game.getCharacter(game.getTurnID());
	player->get_socket()->write("Je bent nu de: " + game->characters[game->getTurnID()]->getName() + "\r\n");
	player->get_socket()->write("Goud: " + std::to_string(player->getGold()) + "\r\n");
	player->get_socket()->write("\r\nGebouwen: \r\n");
	game->printBuildings(player, true);
	player->get_socket()->write("\r\nHandkaarten: \r\n");
	game->printBuildings(player, false);
	player->get_socket()->write("\r\nMaak een keuze: \r\n");
	player->get_socket()->write("[0] Bekijk het goud en gebouwen van de tegenstander (en maak dan een keuze) \r\n");
	player->get_socket()->write("[1] Neem 2 goudstukken \r\n");
	player->get_socket()->write("[2] Neem 2 bouwkaarten en leg er 1 af \r\n");
	player->get_socket()->write("[3] Maak gebruik van de karaktereigenschap van de " + game->characters[game->getTurnID()]->getName() + " \r\n");
}

void TurnStartState::handleCommand(ClientCommand command, std::shared_ptr<GameHandler> gameHandler)
{
	if (!command.is_number()) command.get_player()->get_socket()->write("Input was not a number \r\n");
	switch (std::stoi(command.get_cmd()))
	{
	case 0:
		gameHandler->showGameStatus(command.get_player()->get_socket());
		break;
	case 1:
		if (gameHandler->addGold(command.get_player(), 2))
		{
			gameHandler->changeTurnState(std::make_shared<TurnBuildingActionState>(gameHandler));
		}
		else {
			command.get_player()->get_socket()->write("Er is niet genoeg goud meer in het spel, selecteer een andere optie \r\n");
		}
		break;
	case 2:
		command.get_player()->get_socket()->write("command 2");
		gameHandler->changeTurnState(std::make_shared<TurnBuildingCardState>(gameHandler));
		break;
	case 3:
		command.get_player()->get_socket()->write("command 3");
		break;
	}
}

//std::shared_ptr<TurnState> TurnStartState::nextState()
//{
//
//}