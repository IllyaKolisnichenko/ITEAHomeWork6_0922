#include <iostream>
#include<string>
#include <vector>
#include <fstream>
#include <conio.h>
#include "menupool.h"
#include "Playerspool.h"

std::vector<Players> users;
int i{ 1 };

void writeToFile(Players* pntPlayer) {
	std::ofstream fout("/players.txt", std::ios::app);
	if (!fout.is_open()) {
		std::cout << "Can't create file ";
	}

	fout << pntPlayer->getId() << ' ' << pntPlayer->getName() << ' ' << pntPlayer->getScore() << "\n";
	fout.close();
}

void createFile() {
	std::ofstream fin("/players.txt");

}

bool readFromFile(std::vector<std::string>& data) {
	bool ext{ 1 };
	std::ifstream fin("/players.txt");
	if (!fin.is_open()) {

		return false;
	}
	std::string currentString;
	while (std::getline(fin, currentString)) {
		data.push_back(currentString);

	}
	return true;

}

char mainMenu() {
	char b;
	std::system("cls");
	std::cout << "\t\t\tM E N U\n"
		<< "\t\t1. Players\n"
		<< "\t\t2. Market\n"
		<< "\t\t3. Play\n"
		<< "\t\t4. Exit\n";
	b = _getch();
	while (b != '1' && b != '3' && b != '4') {
		b = _getch();
	}
	return b;
}

void menuPlayers() {
	std::system("cls");
	std::cout << "\t\t1. Create Player\n"
		<< "\t\t2. Exist Player\n"
		<< "\t\t3. Exit\n";

}

void menuChoiseWater() {
	std::cout << "\t\t1. River\n"
		<< "\t\t2. Lake\n"
		<< "\t\t3.Pond\n";
}



int exitPlay() {
	std::cout << "Goodbay...\n";
	system("pause");
	exit(0);
	return 0;

}

void createPlayer() {
	std::vector<std::string>existPlayers;
	std::string ext{};
	int numberOfPlayers{};
	std::string namePlayer;
	std::string id_player;
	Players* pntPlayer = new Players;
	if (readFromFile(existPlayers)) {
		numberOfPlayers = existPlayers.size();
	}
	else createFile();
	std::cout << "Enter name player :";
	std::getline(std::cin, namePlayer);
	pntPlayer->setName(namePlayer);
	pntPlayer->setId(numberOfPlayers + 1);
	pntPlayer->setScore(0);
	pntPlayer->writeToVector(users, *pntPlayer);
	writeToFile(pntPlayer);
	std::cout << "Player created. Please press " << "0" << " for exit.";
	std::getline(std::cin, ext);
	if (ext == "0") {
		std::system("csl");

	}
	delete pntPlayer;
}


int existPlayers() {
	std::vector<std::string>existPlayers;
	bool ext{ 1 };
	int plyr{};
	if (!readFromFile(existPlayers)) {
		std::cout << "Players is absent. Please create Player\n";
		std::cout << "Please press " << "0" << " for exit.";
		std::cin >> ext;
		if (!ext) {
			std::system("csl");
			menuPlayers();
		}

	}

	for (auto& value : existPlayers) {
		std::cout << "Player " << value << " scores" << "\n";
	}


	std::cout << "Please choise Player: ";
	std::cin >> plyr;
	return plyr;




}