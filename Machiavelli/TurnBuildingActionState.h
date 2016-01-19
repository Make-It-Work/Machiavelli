#pragma once
#include "TurnState.h"
#include <vector>
class TurnBuildingActionState :
	public TurnState
{
public:
	TurnBuildingActionState(std::shared_ptr<GameHandler> gameHandler);
	~TurnBuildingActionState();
	//std::shared_ptr<TurnState> nextState();
	void print(std::shared_ptr<Player> player);
	void handleCommand(ClientCommand command, std::shared_ptr<GameHandler> gameHandler);
	std::shared_ptr<TurnState> nextState();
private:
	std::vector<int> buildingCards;
};

