#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <functional>
#include <memory>

#include "Building.h"

class BuildingFactory
{
public:
	BuildingFactory();
	~BuildingFactory();
	static std::unique_ptr<Building> createBuilding(std::string name);
private:
	static std::map<std::string, std::function<std::unique_ptr<Building>()>> factory;
};

