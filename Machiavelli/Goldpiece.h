#pragma once
#include <memory>
#include "Player.hpp"
class Goldpiece
{
private:
	std::shared_ptr<Player> owner = nullptr;
public:
	Goldpiece(std::shared_ptr<Player> stock);
	~Goldpiece();

	std::shared_ptr<Player> getOwner() { return owner; }
	void setOwner(std::shared_ptr<Player> player) { owner = player; }
	void resetOwner(std::shared_ptr<Player> stock) { owner = stock; }
};

