#include <iostream>
#include <fstream>
#include <sstream>
#include <conio.h>
#include <Windows.h>
#include <iterator>
#include "menupool.h"
#include "Playerspool.h"
#include "Fishespool.h"
#include "waterpool.h"
#include "FileWorker.h"

int WeightFish{};
int valGear{};
int valBait{};
int numberOfPlayer = 1;
Water* water = nullptr;
std::vector<Water*> waters;
Player::bait playerBait;
std::vector<std::string> curentPlayer;
std::string nameFish;


void callMenu() {

	switch (mainMenu()) {
		char b;
	case '1':
		menuPlayers();
		b = _getch();
		while (b != '1' && b != '2' && b != '3' && b != '4') {
			b = _getch();
		}
		if (b == '1') {
			createPlayer();
			callMenu();
		}
		if (b == '2') {
			numberOfPlayer = existPlayers();
			callMenu();
		}
		if (b == '3') {
			callMenu();
		}
		break;

	case '2':
		Play();
		break;
	case '3':
		exitPlay();
		break;
	}
}

void Play() {
	std::cout << "Choise a water : \n";
	if (waters.empty()) FileWorker::readWatersFromFile(watersFileName, waters);
	menuChoiseWater();

	int bp;
	do {
		bp = _getch() - 48;
	} while (bp <= 0 || bp > waters.size());
	water = waters.at(bp - 1);
	playMenu();

}

void playMenu()
{
	char gear, bait;
	std::system("cls");
	std::cout << "Choise a fishing gear : \n"
		<< "1. Fishing Rod\n"
		<< "2. Spining\n";
	std::cin >> gear;
	valGear = gear - 49;
	std::system("cls");
	std::cout << "Choise a bait : \n"
		<< "1. Worms\n"
		<< "2. Maggot\n"
		<< "3. Spoon\n";
	std::cin >> bait;
	valBait = bait - 49;
}

char mainMenu() {
	std::system("cls");
	std::cout << "\t\t\tM E N U\n"
		<< "\t\t1. Players\n"
		<< "\t\t2. Play\n"
		<< "\t\t3. Exit\n";

	char b;
	do {
		b = _getch();
	} while (b != '1' && b != '2' && b != '3');
	return b;
}

void menuPlayers() {
	std::system("cls");
	std::cout << "\t\t1. Create Player\n"
		<< "\t\t2. Exist Player\n"
		<< "\t\t3. Exit\n";

}

void menuChoiseWater() {
	for (int i = 0; i < waters.size(); i++) {
		std::cout << "\t\t" << i + 1 << " " << waters[i]->getName() << std::endl;
	}
}

int exitPlay() {
	std::cout << "Goodbay...\n";
	system("pause");
	exit(0);
	return 0;
}

int main()
{
	Player Player;
	Fish* fish;
	Player.setId(numberOfPlayer);
	srand(time(NULL));
	callMenu();
	playerBait = Player.getBait(valBait);
	bool again = true;
	std::cout << "You cast your fishing rod...\n";
	while (again) {
		std::cout << "wait...\r";
		Sleep(2000);

		fish = water->WhatIsFish();
		int saturation = fish->getSaturation();
		WeightFish = fish->getWeight();
		nameFish = fish->getSpecies();

		std::string CautchOrNot = Player.cautchFish(Player.getFishingGear(valGear), saturation, WeightFish, playerBait, nameFish);

		again = isFishCatched(CautchOrNot);
	}
	return 0;
}

bool isFishCatched(std::string& CautchOrNot)
{
	bool again = false;
	if ((CautchOrNot == "not") || (CautchOrNot == "cautch")) {
		std::cout << "A G A I N ?\n"
			<< "Please press '1'\n"
			<< "Please press '0' for exit to Main Menu\n";
		char b;
		do {
			b = _getch();
		} while (b != '1' && b != '0');

		if (b == '1') {
			again = true;
		}
		else {
			if (FileWorker::readFromFile(curentPlayer, playerFileName)) updatePlayerInfo();
			callMenu();
		}
	}
	if (CautchOrNot == "wait") {
		again = true;
	}
	return again;
}

void updatePlayerInfo()
{
	std::stringstream ss{ curentPlayer.at(numberOfPlayer - 1) };
	std::string strTemp;
	std::vector<std::string>temp;
	while (std::getline(ss, strTemp, ' '))
		temp.push_back(strTemp);
	int curentScore = std::stoi(temp[2]) + WeightFish;
	temp[2] = std::to_string(curentScore);
	strTemp.erase();
	strTemp = strTemp.append(temp[0] + ' ' + temp[1] + ' ' + temp[2]);
	curentPlayer[numberOfPlayer - 1] = strTemp;
	remove(playerFileName.c_str());
	std::ofstream fout(playerFileName, std::ios::app);
	if (!fout.is_open()) {
		std::cout << "Can't create file ";
	}
	for (auto& val : curentPlayer) {
		fout << val << "\n";
	}
	fout.close();
}
