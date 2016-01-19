#include "stdafx.h"
#include "TurnBuildingActionState.h"
#include "TurnCharacterActionState.h"
#include "TurnStartState.h"
#include "GameHandler.h"

TurnBuildingActionState::TurnBuildingActionState(std::shared_ptr<GameHandler> gh)
{
	game = gh;
}


TurnBuildingActionState::~TurnBuildingActionState()
{
}

void TurnBuildingActionState::print(std::shared_ptr<Player> player)
{
	player->get_socket()->write("\r\n Kies een van de volgende bouwkaarten om te bouwen: \r\n");
	buildingCards = game->buildingIdsForPlayer(player);
	player->get_socket()->write("[0] - Niet bouwen \r\n");
	for (int id : buildingCards)
	{
			player->get_socket()->write("[" + std::to_string(id) + "]" + game->getBuildingString(id) + "\r\n");
	}
}

void TurnBuildingActionState::handleCommand(ClientCommand command, std::shared_ptr<GameHandler> gameHandler)
{
	if (!command.is_number()) {
		command.get_player()->get_socket()->write("Input was not a number \r\n");
		return;
	} 
	int i = stoi(command.get_cmd());
	if (i == 0) {
		game->changeTurnState(nextState());
		
	}
	else if (std::find(buildingCards.begin(), buildingCards.end(), i) != buildingCards.end())
	{
		if (game->buildBuilding(command.get_player(), i) == "oke") {
			game->changeTurnState(nextState());
		}
	}
	else
	{
		command.get_player()->get_socket()->write("You don't own this building \r\n");
	}
}

std::shared_ptr<TurnState> TurnBuildingActionState::nextState() {
	return std::make_shared<TurnCharacterActionState>(game);
}

