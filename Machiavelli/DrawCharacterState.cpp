#include "stdafx.h"
#include "DrawCharacterState.h"
#include "GameHandler.h"
#include "RandomEngine.h"
#include "CharacterHandler.h"

DrawCharacterState::DrawCharacterState(std::shared_ptr<GameHandler> gameHandler)
{
	game = gameHandler;
	cardId = RandomEngine::drawCharacterCard(gameHandler->getCharacterHandler().getCharacters());
	if (cardId != -1) {
		game->getCharacterHandler().layOffCharacterCard(cardId);
	}
}


DrawCharacterState::~DrawCharacterState()
{

}

void DrawCharacterState::print(std::shared_ptr<Player> player)
{
	player->get_socket()->write("De bovenste kaart was de " +
		game->getCharacterHandler().getCharacterRef(cardId).getName() +
		". Kies een van de onderstaande kaarten:\r\n"
		);
	for each (const auto& kv in game->getCharacterHandler().getCharacters())
	{
		if (kv.second->getOwner() == nullptr && kv.second->getOwner() != game->getStock()) {
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
		game->getCharacterHandler().pickCharacterCard(std::stoi(s_pickedCard), command.get_player());
		game->nextTurn();
	}
	else {
		command.get_player()->get_socket()->write("Something went wrong, please pick one of the numbers: \r\n");
	}
}