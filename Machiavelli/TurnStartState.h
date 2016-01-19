#pragma once
#include "TurnState.h"
#include "GameHandler.h"
#include "Player.hpp"
#include "Character.h"

class TurnStartState : public TurnState
{
public:
	TurnStartState(std::shared_ptr<GameHandler> gameHandler);
	~TurnStartState();
	//std::shared_ptr<TurnState> nextState();
	void print(std::shared_ptr<Player> player);
	void handleCommand(ClientCommand command, std::shared_ptr<GameHandler> gameHandler);
private:
	std::shared_ptr<GameHandler> game;
};

