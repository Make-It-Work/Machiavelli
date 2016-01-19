#pragma once
#include "TurnState.h"

class DrawCharacterState : public TurnState
{
public:
	//TurnStartState(GameHandler& gh);
	DrawCharacterState(std::shared_ptr<GameHandler> gameHandler);
	~DrawCharacterState();
	//std::shared_ptr<TurnState> nextState();
	void print(std::shared_ptr<Player> player);
	void handleCommand(ClientCommand command, std::shared_ptr<GameHandler> gameHandler);
	virtual std::string getName() { return "drawing"; };
	int getCard() { return cardId; };
private:
	std::shared_ptr<GameHandler> game;
	int cardId = -1;
};

