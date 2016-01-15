#include "stdafx.h"
#include "BuildingFactory.h"
#include "Bibliotheek.h"
#include "Burcht.h"
#include "Drakenpoort.h"
#include "Gevangenis.h"
#include "Handelshuis.h"
#include "Haven.h"
#include "HofDerWonderen.h"
#include "Kasteel.h"
#include "Kathedraal.h"
#include "Kerk.h"
#include "Kerker.h"
#include "Kerkhof.h"
#include "Klooster.h"
#include "Laboratorium.h"
#include "Landgoed.h"
#include "Markt.h"
#include "Observatorium.h"
#include "Paleis.h"
#include "Raadhuis.h"
#include "SchoolVoorMagiers.h"
#include "Taveerne.h"
#include "Tempel.h"
#include "Toernooiveld.h"
#include "Universiteit.h"
#include "Wachttoren.h"
#include "Werkplaats.h"
#include "Winkels.h"

std::map<std::string, std::function<std::unique_ptr<Building>()>> BuildingFactory::factory;
BuildingFactory::BuildingFactory()
{
	factory.emplace("Bibliotheek", []() -> std::unique_ptr<Building> {
		return std::unique_ptr<Building>(new Bibliotheek);
	});
	factory.emplace("Burcht", []() -> std::unique_ptr<Building> {
		return std::unique_ptr<Building>(new Burcht);
	});
	factory.emplace("Drakenpoort", []() -> std::unique_ptr<Building> {
		return std::unique_ptr<Building>(new Drakenpoort);
	});
	factory.emplace("Gevangenis", []() -> std::unique_ptr<Building> {
		return std::unique_ptr<Building>(new Gevangenis);
	});
	factory.emplace("Handelshuis", []() -> std::unique_ptr<Building> {
		return std::unique_ptr<Building>(new Handelshuis);
	});
	factory.emplace("Haven", []() -> std::unique_ptr<Building> {
		return std::unique_ptr<Building>(new Haven);
	});
	factory.emplace("Hof", []() -> std::unique_ptr<Building> {
		return std::unique_ptr<Building>(new HofDerWonderen);
	});
	factory.emplace("Kasteel", []() -> std::unique_ptr<Building> {
		return std::unique_ptr<Building>(new Kasteel);
	});
	factory.emplace("Kathedraal", []() -> std::unique_ptr<Building> {
		return std::unique_ptr<Building>(new Kathedraal);
	});
	factory.emplace("Kerk", []() -> std::unique_ptr<Building> {
		return std::unique_ptr<Building>(new Kerk);
	});
	factory.emplace("Kerker", []() -> std::unique_ptr<Building> {
		return std::unique_ptr<Building>(new Kerker);
	});
	factory.emplace("Kerkhof", []() -> std::unique_ptr<Building> {
		return std::unique_ptr<Building>(new Kerkhof);
	});
	factory.emplace("Klooster", []() -> std::unique_ptr<Building> {
		return std::unique_ptr<Building>(new Klooster);
	});
	factory.emplace("Laboratorium", []() -> std::unique_ptr<Building> {
		return std::unique_ptr<Building>(new Laboratorium);
	});
	factory.emplace("Landgoed", []() -> std::unique_ptr<Building> {
		return std::unique_ptr<Building>(new Landgoed);
	});
	factory.emplace("Markt", []() -> std::unique_ptr<Building> {
		return std::unique_ptr<Building>(new Markt);
	});
	factory.emplace("Observatorium", []() -> std::unique_ptr<Building> {
		return std::unique_ptr<Building>(new Observatorium);
	});
	factory.emplace("Paleis", []() -> std::unique_ptr<Building> {
		return std::unique_ptr<Building>(new Paleis);
	});
	factory.emplace("Raadhuis", []() -> std::unique_ptr<Building> {
		return std::unique_ptr<Building>(new Raadhuis);
	});
	factory.emplace("School", []() -> std::unique_ptr<Building> {
		return std::unique_ptr<Building>(new SchoolVoorMagiers);
	});
	factory.emplace("Taveerne", []() -> std::unique_ptr<Building> {
		return std::unique_ptr<Building>(new Taveerne);
	});
	factory.emplace("Tempel", []() -> std::unique_ptr<Building> {
		return std::unique_ptr<Building>(new Tempel);
	});
	factory.emplace("Toernooiveld", []() -> std::unique_ptr<Building> {
		return std::unique_ptr<Building>(new Toernooiveld);
	});
	factory.emplace("Universiteit", []() -> std::unique_ptr<Building> {
		return std::unique_ptr<Building>(new Universiteit);
	});
	factory.emplace("Wachttoren", []() -> std::unique_ptr<Building> {
		return std::unique_ptr<Building>(new Wachttoren);
	});
	factory.emplace("Werkplaats", []() -> std::unique_ptr<Building> {
		return std::unique_ptr<Building>(new Werkplaats);
	});
	factory.emplace("Winkels", []() -> std::unique_ptr<Building> {
		return std::unique_ptr<Building>(new Winkels);
	});
}

BuildingFactory::~BuildingFactory()
{
}

std::unique_ptr<Building> BuildingFactory::createBuilding(std::string s) {
	std::string delimiter = ";";
	size_t pos = 0;
	std::string token;
	pos = s.find(delimiter);
	std::string name = s.substr(0, pos);

	auto it = factory.find(name);
	if (it != factory.end()) {
		std::function<std::unique_ptr<Building>()> execute = it->second;
		return execute();
	}
	else {
		std::cerr << "key '" << name << "' not found" << '\n';
	}
}