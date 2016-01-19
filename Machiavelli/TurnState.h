#pragma once
#include <memory>

#include "ClientCommand.h"

class Player;
class GameHandler;
class Character;
class TurnState
{
public:
	TurnState() {};
	~TurnState() {};
	//virtual std::shared_ptr<TurnState> nextState() {};
	virtual void print(std::shared_ptr<Player> player) {};
	virtual void handleCommand(ClientCommand command, std::shared_ptr<GameHandler> gameHandler) {};
	virtual std::string getName() { return "turn"; };
protected:
	std::shared_ptr<GameHandler> game = nullptr;
};