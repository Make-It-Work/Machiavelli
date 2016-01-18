#pragma once
#include "TurnState.h"
#include "GameHandler.h"

class TurnStartState : public TurnState
{
public:
	//TurnStartState(GameHandler& gh);
	TurnStartState();
	~TurnStartState();
	//std::shared_ptr<TurnState> nextState();
	void print(std::shared_ptr<Player> player, const Character& chr);
	void handleCommand(ClientCommand command);
private:
	GameHandler game;
};

