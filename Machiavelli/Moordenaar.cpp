#include "stdafx.h"
#include "Moordenaar.h"
#include "ClientCommand.h"

Moordenaar::Moordenaar()
{
	name = "Moordenaar";
	id = 1;
}


Moordenaar::~Moordenaar()
{
}

bool Moordenaar::execute(ClientCommand command, std::shared_ptr<GameHandler> game) const
{
	if (!command.is_number()) {
		return false;
	}
	else {
		int killed = stoi(command.get_cmd());
		if (killed > 0 && killed < 9) {
			game->killCharacter(killed);
		}
		else {
			//Geen geldige moord
			return false;
		}
	}
}

std::string Moordenaar::getActionDescription(std::shared_ptr<GameHandler> game) const
{
	std::string s = "Kies een karakter om te vermoorden: \r\n";
	s += "[2] Dief \r\n";
	s += "[3] Magier \r\n";
	s += "[4] Koning \r\n";
	s += "[5] Prediker \r\n";
	s += "[6] Koopman \r\n";
	s += "[7] Bouwmeester \r\n";
	s += "[8] Condottiere \r\n";
	return s;
}

