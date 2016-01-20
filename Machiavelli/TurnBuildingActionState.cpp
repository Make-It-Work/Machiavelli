#include "stdafx.h"
#include "TurnBuildingActionState.h"
#include "TurnCharacterActionState.h"
#include "TurnStartState.h"
#include "GameHandler.h"
#include "Building.h"

TurnBuildingActionState::TurnBuildingActionState(std::shared_ptr<GameHandler> gh)
{
	game = gh;
	for (int id : game->buildingIdsForPlayer(game->getCurPlayer()))
	{
		const Building& building = game->getBuilding(id);
		if (!building.isPlayed() && game->getCurPlayer()->getGold() >= building.getCost()) {
			buildingCards.push_back(id);
		}
	}
}


TurnBuildingActionState::~TurnBuildingActionState()
{
}

void TurnBuildingActionState::print(std::shared_ptr<Player> player)
{
	player->get_socket()->write("\r\n Kies een van de volgende bouwkaarten om te bouwen: \r\n");
	player->get_socket()->write("[0] - Niet bouwen \r\n");
	for (int i = 0; i < buildingCards.size(); i++)
	{
		player->get_socket()->write("[" + std::to_string(i + 1) + "]" + game->getBuildingString(buildingCards[i]) + "\r\n");
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
	else if (i > 0 && i <= buildingCards.size())
	{
		if (game->buildBuilding(command.get_player(), buildingCards[i - 1]) == "oke") {
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

