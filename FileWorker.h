#pragma once
#include "Helpers.h"
#include "waterpool.h"
#include "Playerspool.h"

const std::string playerFileName = "players.txt";
const std::string watersFileName = "waters.txt";

class FileWorker {
public:
	static void readWatersFromFile(const std::string& fileName, std::vector<Water*>& waters) {
		std::ifstream fin(fileName);
		if (!fin.is_open()) {
			std::cout << "PROBLEM WITH OPEN FILE\n";
			return;
		}

		std::string currentString;
		while (std::getline(fin, currentString)) {
			auto data = Helper::split(currentString, " ");
			Water* water = new Water(data[0], stoi(data[1]));
			waters.push_back(water);
		}
	};
	static void writeToFile(const std::string& fileName, Player* pntPlayer) {
		std::ofstream fout(fileName, std::ios::app);
		if (!fout.is_open()) {
			std::cout << "Can't create file ";
		}
		fout << pntPlayer->getId() << ' ' << pntPlayer->getName() << ' ' << pntPlayer->getScore() << "\n";
		fout.close();
	}
	static void createFile(const std::string& fileName) {
		std::ofstream fin(fileName);
		fin.close();
	}
	static bool readFromFile(std::vector<std::string>& data, const std::string& fileName) {
		bool ext = true;
		std::ifstream fin(fileName);
		if (!fin.is_open()) {
			return false;
		}

		std::string currentString;
		while (std::getline(fin, currentString)) {
			data.push_back(currentString);
		}
		return true;
	}
};