#pragma once
#include <memory>
#include "Player.hpp"
#include "ClientCommand.h"
#include "Character.h"

class TurnState
{
public:
	TurnState() {};
	~TurnState() {};
	//virtual std::shared_ptr<TurnState> nextState() {};
	virtual void print(std::shared_ptr<Player> player, const Character& chr) {};
	virtual void handleCommand(ClientCommand command) {};
private:

};