#pragma once
#include "TurnState.h"
#include "GameHandler.h"

class TurnBuildingCardState : public TurnState
{
public:
	//TurnStartState(GameHandler& gh);
	TurnBuildingCardState(std::shared_ptr<GameHandler> gameHandler);
	~TurnBuildingCardState();
	//std::shared_ptr<TurnState> nextState();
	void print(std::shared_ptr<Player> player);
	void handleCommand(ClientCommand command, std::shared_ptr<GameHandler> gameHandler);
private:
	std::vector<int> buildingCards;
};
