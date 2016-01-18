#pragma once
#include "TurnState.h"
#include "GameHandler.h"

class TurnStartState : public TurnState
{
public:
	TurnStartState(GameHandler gh);
	~TurnStartState();
	std::shared_ptr<TurnState> nextState();
	void print(std::shared_ptr<Player> player);
	void handleCommand(ClientCommand command);
private:
	GameHandler game;
};

