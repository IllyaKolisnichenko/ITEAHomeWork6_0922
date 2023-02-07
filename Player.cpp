#include <iostream>
#include<string>
#include <vector>
#include <fstream>
#include <conio.h>
#include "menupool.h"
#include "Playerspool.h"
#include "waterpool.h"
#include "FileWorker.h"
#pragma once
Player* inputPlayer(int numberOfPlayers)
{
	Player* pntPlayer = new Player();
	std::string namePlayer;

	std::cout << "Enter name player :";
	std::getline(std::cin, namePlayer);
	pntPlayer->setName(namePlayer);
	pntPlayer->setId(numberOfPlayers + 1);
	pntPlayer->setScore(0);
	return pntPlayer;
}

void createPlayer() {
	std::vector<std::string> existPlayers;
	int numberOfPlayers = 0;

	if (FileWorker::readFromFile(existPlayers, playerFileName)) {
		numberOfPlayers = existPlayers.size();
	}
	else {
		FileWorker::createFile(playerFileName);
	}

	Player* pntPlayer = inputPlayer(numberOfPlayers);
	FileWorker::writeToFile(playerFileName, pntPlayer);
	handleToExitFromPlayerMenu();
	delete pntPlayer;
}

void handleToExitFromPlayerMenu()
{
	std::cout << "Please press " << "0" << " for exit.";
	std::string ext;
	std::getline(std::cin, ext);
	if (ext == "0") {
		std::system("csl");
	}
}

int existPlayers() {
	std::vector<std::string> existPlayers;
	bool ext = true;
	if (!FileWorker::readFromFile(existPlayers, playerFileName)) {
		std::cout << "Players is absent. Please create Player\n";
		std::cout << "Please press " << "0" << " for exit.";
		std::cin >> ext;
		if (ext == 1) {
			std::system("csl");
			menuPlayers();
		}
	}

	for (auto& value : existPlayers) {
		std::cout << "Player: " << value << " scores" << "\n";
	}

	std::cout << "Please choise Player: ";
	int plyr;
	std::cin >> plyr;
	return plyr;
}