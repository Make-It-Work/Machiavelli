#include "stdafx.h"
#include "Condottiere.h"
#include "Building.h"

Condottiere::Condottiere()
{
	name = "Condottiere";
	id = 8;
}


Condottiere::~Condottiere()
{
}

void Condottiere::getExtraGoldPieces(std::shared_ptr<Player> player, std::shared_ptr<GameHandler> game) const
{
	int amount = 0;
	for (int buildingId : game->buildingIdsForPlayer(player)) {
		const Building& building = game->getBuilding(buildingId);
		if (building.isPlayed() && building.getColor() == "rood") {
			amount++;
		}
	}
	game->addGold(player, amount);
}

bool Condottiere::execute(ClientCommand command, std::shared_ptr<GameHandler> game) const
{

	std::vector<int> buildingCards;
	for (int b_id : game->buildingIdsForPlayer(game->getNextPlayer(owner)))
	{
		const Building& building = game->getBuilding(b_id);
		if (building.isPlayed()) {
			buildingCards.push_back(b_id);
		}
	}

	if (!command.is_number()) {
		command.get_player()->get_socket()->write("Input was not a number \r\n");
		return false;
	}
	int i = stoi(command.get_cmd());
	if (i == 0) {
		return true;
	}
	else if (i > 0 && i <= buildingCards.size())
	{
		return game->removeBuilding(buildingCards[i - 1], owner);
	}
	else
	{
		return false;
		command.get_player()->get_socket()->write("You don't own this building \r\n");
	}
	return true;
}

std::string Condottiere::getActionDescription(std::shared_ptr<GameHandler> game) const {
	std::vector<int> buildingCards;
	owner->get_socket()->write("Een gebouw kiezen om te vernietigen \r\n");
	owner->get_socket()->write("[0] - Niets vernietigen \r\n");
	if (game->characters[5]->getOwner() != game->getNextPlayer(owner)) {
		for (int b_id : game->buildingIdsForPlayer(game->getNextPlayer(owner)))
		{
			const Building& building = game->getBuilding(b_id);
			if (building.isPlayed()) {
				buildingCards.push_back(b_id);
			}
		}
		for (int i = 0; i < buildingCards.size(); i++)
		{
			const Building& building = game->getBuilding(buildingCards[i]);
			owner->get_socket()->write("[" + std::to_string(i + 1) + "]" + game->getBuildingString(buildingCards[i]) + " voor " + std::to_string(building.getCost() - 1) + " goud\r\n");
		}
	}
	return "";
}

