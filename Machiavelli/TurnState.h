#pragma once
#include <memory>
#include "Player.hpp"
#include "ClientCommand.h"

class TurnState
{
public:
	TurnState() {};
	~TurnState() {};
	virtual std::shared_ptr<TurnState> nextState() {};
	virtual void print(std::shared_ptr<Player> player) {};
	virtual void handleCommand(ClientCommand command) {};
private:

};