#pragma once
#include "TurnState.h"

class TurnCharacterActionState :
	public TurnState
{
public:
	TurnCharacterActionState(std::shared_ptr<GameHandler> gameHandler);
	~TurnCharacterActionState();
	void print(std::shared_ptr<Player> player);
	void handleCommand(ClientCommand command, std::shared_ptr<GameHandler> gameHandler);
	std::shared_ptr<TurnState> nextState();
private:
};

