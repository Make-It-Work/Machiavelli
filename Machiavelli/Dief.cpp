#include "stdafx.h"
#include "Dief.h"


Dief::Dief()
{
	name = "Dief";
	id = 2;
}


Dief::~Dief()
{
}

bool Dief::execute(ClientCommand command, std::shared_ptr<GameHandler> game) const
{
	if (!command.is_number()) {
		return false;
	}
	else {
		int stolen = stoi(command.get_cmd());
		if (stolen > 0 && stolen < charactersToSteal.size()) {
			game->stealCharacter(charactersToSteal[stolen - 1], command.get_player());
			return true;
		}
		else {
			//Geen geldige steal
			return false;
		}
	}
}

std::string Dief::getActionDescription(std::shared_ptr<GameHandler> game) const {
	std::string s = "Kies iemand om te bestelen: \r\n";
	std::vector<int> characterIds;
	for (int i = 3; i < 8; i++) {
		//Begint bij 2 om de moordenaar en dief over te slaan
		const Character& chr = game->getCharacter(i);
		if (!chr.isKilled()) {
			characterIds.push_back(chr.getId());
			s += "[" + std::to_string(i - 2) + "] " + chr.getName() + "\r\n";
		}
	}
	return s;
}
