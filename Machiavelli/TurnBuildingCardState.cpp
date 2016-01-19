#include "stdafx.h"
#include "Character.h"
#include "TurnBuildingCardState.h"
#include "TurnBuildingActionState.h"
#include "GameHandler.h"

TurnBuildingCardState::TurnBuildingCardState(std::shared_ptr<GameHandler> gameHandler)
{
	game = gameHandler;
	buildingCards = gameHandler->drawBuildingCards(2);
}


TurnBuildingCardState::~TurnBuildingCardState()
{

}

void TurnBuildingCardState::print(std::shared_ptr<Player> player, const Character& chr)
{

	player->get_socket()->write("\r\nKies een van de volgende bouwkaarten: \r\n");
	int i = 0;
	for(int id : buildingCards)
	{
		player->get_socket()->write("[" + std::to_string(i++) + "]" + game->getBuildingString(id) + "\r\n");
	}
}

void TurnBuildingCardState::handleCommand(ClientCommand command, std::shared_ptr<GameHandler> gameHandler)
{
	if (!command.is_number()) {
		command.get_player()->get_socket()->write("Input was not a number \r\n");
		return;
	}
	int i = stoi(command.get_cmd());
	if (i > buildingCards.size()) {
		command.get_player()->get_socket()->write("Number was too high \r\n");
		return;
	}
	int id = buildingCards[i];
	gameHandler->assignBuilding(id, command.get_player());
	gameHandler->changeTurnState(std::make_shared<TurnBuildingActionState>(gameHandler));
}