#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <conio.h>
#include <string>
#include <Windows.h>
#include <iterator>
#include "menupool.h"
#include "Playerspool.h"
#include "Fishespool.h"
#include "waterpool.h"

int WeightFish{};

int saturation{};
int valGear{};
int valBait{};
int numberOfPlayer{ 1 };
char bp;
std::string water;
char gear{};
char bait{};
Players::bait Plbt;
std::vector<std::string> curentPlayer;
std::string nameFish;

void Play();

void callMenu() {

	switch (mainMenu()) {
	case '1':
		char b;
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

	case '3':
		Play();
		break;
	case '4':
		exitPlay();

		break;

	}

}

void Play() {
	std::cout << "Choise a water : \n";
	menuChoiseWater();
	char bp;
	bp = _getch();
	while (bp != '1' && bp != '2' && bp != '3') {
		bp = _getch();
	}
	switch (bp) {
	case '1':
		water = Waters::getNameRiver();
		
		break;
	case '2':
		water = Waters::getNameLake();
		
		break;
	case '3':
		water = Waters::getNamePond();
		
		break;
	}
	char gear{};
	char bait{};

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



int main()
{

	Players Player;
	Carps Carp;
	Crucians Crucian;
	Pikes Pike;
	FishGoby FishGoby;
	Player.setId(numberOfPlayer);
	srand(time(NULL));
	callMenu();
	Plbt = Player.getBait(valBait);
	bool again{ true };
	std::cout << "You cast your fishing rod...\n";
	while (again) {

		again = false;
		std::cout << "wait...\r";
		Sleep(5000);
		if (water == "River") { nameFish = Waters::WhatIsFishRiver(); }
		if (water == "Lake") { nameFish = Waters::WhatIsFishLake(); }
		if (water == "Pond") { nameFish = Waters::WhatIsFishPond(); }

		if (nameFish == "Carp") {
			saturation = Carp.getSaturation();
			WeightFish = Carp.getWeight();

		}
		if (nameFish == "Crucian") {
			saturation = Crucian.getSaturation();
			WeightFish = Crucian.getWeight();

		}
		if (nameFish == "Pike") {
			saturation = Pike.getSaturation();
			WeightFish = Pike.getWeight();

		}

		if (nameFish == "FishGoby") {
			saturation = FishGoby.getSaturation();
			WeightFish = FishGoby.getWeight();

		}

		std::string CautchOrNot = Player.cautchFish(Player.getFishingGear(valGear), saturation, WeightFish,
			Plbt, nameFish);

		if ((CautchOrNot == "not") || (CautchOrNot == "cautch")) {

			std::cout << "A G A I N ?\n"
				<< "Please press '1'\n"
				<< "Please press '0' for exit to Main Menu\n";
			char b;
			b = _getch();
			while (b != '1' && b != '0') {
				b = _getch();
			}
			if (b == '1') {
				again = true;

			}
			if (b == '0') {
				if (readFromFile(curentPlayer)) {
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
					remove("/players.txt");
					std::ofstream fout("/players.txt", std::ios::app);
					if (!fout.is_open()) {
						std::cout << "Can't create file ";
					}
					for (auto& val : curentPlayer) {
						fout << val << "\n";
					}
					fout.close();




				}
				callMenu();

			}
		}
		if (CautchOrNot == "wait") {
			again = true;
		}

	}

	return 0;
}