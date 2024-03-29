#include "stdafx.h"
#include "TurnCharacterActionState.h"
#include "GameHandler.h"
#include "Character.h"

TurnCharacterActionState::TurnCharacterActionState(std::shared_ptr<GameHandler> gh)
{
	game = gh;
}

TurnCharacterActionState::~TurnCharacterActionState()
{
}

void TurnCharacterActionState::print(std::shared_ptr<Player> player)
{
	const Character& chr = game->getCharacterRef(game->getTurnID());
	player->get_socket()->write("\r\n Omdat je de " + chr.getName() + " bent, mag je: \r\n");
	player->get_socket()->write(chr.getActionDescription(game) + "\r\n");
}

void TurnCharacterActionState::handleCommand(ClientCommand command, std::shared_ptr<GameHandler> gameHandler)
{
	gameHandler->getCurPlayer()->get_socket()->write("Executed action \r\n");
	const Character& chr = game->getCharacterRef(game->getTurnID());
	if (chr.execute(command, gameHandler)) {
		game->nextTurn();
	}
}

std::shared_ptr<TurnState> TurnCharacterActionState::nextState() {
	return std::make_shared<TurnCharacterActionState>(game);
}