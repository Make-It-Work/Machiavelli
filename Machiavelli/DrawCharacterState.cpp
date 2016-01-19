#include "stdafx.h"
#include "DrawCharacterState.h"
#include "GameHandler.h"
#include "RandomEngine.h"

DrawCharacterState::DrawCharacterState(std::shared_ptr<GameHandler> gameHandler)
{
	game = gameHandler;
	cardId = RandomEngine::drawCharacterCard(gameHandler->characters);
	if (cardId != -1) {
		gameHandler->layOffCharacterCard(cardId);
	}
}


DrawCharacterState::~DrawCharacterState()
{

}

void DrawCharacterState::print(std::shared_ptr<Player> player)
{
	player->get_socket()->write("De bovenste kaart was de " +
		game->characters[cardId]->getName() +
		". Kies een van de onderstaande kaarten:\r\n"
		);
	for each (const auto& kv in game->characters)
	{
		if (kv.second->getOwner() == nullptr) {
			player->get_socket()->write(std::to_string(kv.second->getId()));
			player->get_socket()->write(" " + kv.second->getName() + "\r\n");
		}
	}
}

void DrawCharacterState::handleCommand(ClientCommand command, std::shared_ptr<GameHandler> gameHandler)
{
	std::string s_pickedCard = command.get_cmd();
	if (std::stoi(s_pickedCard) != NULL) {
		command.get_player()->get_socket()->write("you picked " + s_pickedCard + "\r\n");
		game->pickCharacterCard(std::stoi(s_pickedCard), command.get_player());
		game->nextTurn();
	}
	else {
		command.get_player()->get_socket()->write("Something went wrong, please pick one of the numbers: \r\n");
	}
}