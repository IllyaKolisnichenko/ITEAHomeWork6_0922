#pragma once
#include <iostream>
#include "Helpers.h"

class Water {
private:
	std::string _name;
	int _chanceToFish;
	std::vector<Fish*> fishes;

	Fish* catchFist() {
		return fishes.at(rand() % fishes.size());
	}
	void insertFishesDataInWater() {
		std::ifstream fin("fishes.txt");
		if (!fin.is_open()) {
			std::cout << "PROBLEM WITH OPEN FILE\n";
			return;
		}

		std::string currentString;
		while (std::getline(fin, currentString)) {
			auto data = Helper::split(currentString, " ");
			Fish* fish = new Fish(stoi(data[0]), stoi(data[1]), data[2]);
			fishes.push_back(fish);
		}
	}
public:
	Water(const std::string& name, int chanceToFish)
	{
		_name = name;
		_chanceToFish = chanceToFish;
	}
	std::string getName() { return _name; }

	Fish* WhatIsFish() {
		int x = 40;
		int y = 80;
		if (fishes.empty()) insertFishesDataInWater();
		return catchFist();
	}
};
