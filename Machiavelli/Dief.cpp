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

	std::vector<int> characterIds;
	for (int i = 3; i < 8; i++) {
		//Begint bij 2 om de moordenaar en dief over te slaan
		const Character& chr = game->getCharacter(i);
		if (!chr.isKilled()) {
			characterIds.push_back(chr.getId());
		}
	}
	if (!command.is_number()) {
		owner->get_socket()->write("Ongeldige input \r\n");
		return false;
	}
	else {
		int stolen = stoi(command.get_cmd());
		if (stolen == 0)
		{
			return true;
		}
		else if (stolen > 0 && stolen <= characterIds.size()) {
			game->stealCharacter(characterIds[stolen - 1], command.get_player());
			return true;
		}
		else {
			//Geen geldige steal
		owner->get_socket()->write("Ongeldige input 2 \r\n");
			return false;
		}
	}
}

std::string Dief::getActionDescription(std::shared_ptr<GameHandler> game) const {
	std::string s = "Kies iemand om te bestelen: \r\n";
	s += "[0] niemand: \r\n";
	std::vector<int> characterIds;
	int j = 1;
	for (int i = 3; i < 8; i++) {
		//Begint bij 2 om de moordenaar en dief over te slaan
		const Character& chr = game->getCharacter(i);
		if (!chr.isKilled()) {
			characterIds.push_back(chr.getId());
			s += "[" + std::to_string(j) + "] " + chr.getName() + "\r\n";
			j++;
		}
	}
	return s;
}
