#pragma once
#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <Windows.h>
#include "Fishespool.h"


class Player {

public:

	enum fishingGear {
		fishingRod,
		spinning,
	};

	enum bait {
		worms,
		maggot,
		spoon,
	};

	void setName(std::string& name) {
		name_ = name;
	}

	void setId(int id) {
		id_player_ = id;
	}

	int getScore() {
		return score_;
	}

	void setScore(int fishWeight) {
		score_ = fishWeight;
	}

	static std::pair<fishingGear, int> getFishingGear(int& gear) {
		fishingGear playerGears(static_cast<fishingGear>(gear));
		return { playerGears, gear == 1 ? maxWeightFishesSpining : maxWeightFishesRod };
	}

	static bait getBait(int& bait1) {
		return static_cast<bait>(bait1);
	}

	std::string cautchFish(std::pair<fishingGear, int> fishingGear, int saturation, int WeightFish, bait choosenBait, std::string nameFish) {

		if ((saturation < 5) && (fishingGear.first == fishingRod) && (choosenBait == bait::worms || bait::maggot)) {
			std::cout << "nibble....nibble...(kluet.....kluet)\n";

			Sleep(5000);
			if (WeightFish < 1500 && fishingGear.second) {
				std::cout << "You cautch " << nameFish << "\n";
				std::cout << "weight =" << WeightFish << " grams" << "\n";
				Player::setScore(Player::getScore() + WeightFish);
				return "cautch";

			}
			else if (WeightFish > 1500 && fishingGear.second) {
				std::cout << "You do not catch fish. it was a very big fish\n";
				return "not";
			}

		}

		if ((saturation < 5) && (fishingGear.first == spinning) && (choosenBait == bait::worms || bait::maggot)) {
			std::cout << "nibble....nibble...(kluet.....kluet)\n";
			Sleep(5000);
			if (WeightFish < 3000 && fishingGear.second) {
				std::cout << "You cautch " << nameFish << "\n";
				std::cout << "weight =" << WeightFish << " grams" << "\n";
				Player::setScore(Player::getScore() + WeightFish);
				return "cautch";

			}
			else if (WeightFish > 3000 && fishingGear.second) {
				std::cout << "You do not catch fish. it was a very big fish\n";
				return "not";
			}

		}

		if ((saturation < 5) && (fishingGear.first == spinning) && (choosenBait == bait::spoon)) {
			while (!(nameFish == "Pike")) {
				return "wait";
			}
			std::cout << "nibble....nibble...(kluet.....kluet)\n";
			Sleep(5000);
			if (WeightFish < 3000 && fishingGear.second) {
				std::cout << "You cautch " << nameFish << "\n";
				std::cout << "weight =" << WeightFish << " grams" << "\n";
				Player::setScore(Player::getScore() + WeightFish);
				return "cautch";

			}
			else if (WeightFish > 3000 && fishingGear.second) {
				std::cout << "You do not catch fish. it was a very big fish\n";
				return "not";
			}
		}

		return "wait";
	}
	std::string getName() {
		return name_;
	}
	int getId() {
		return id_player_;
	}
private:
	int id_player_;
	std::string name_;
	int score_ = 0;

	static constexpr int maxWeightFishesRod = 1500;
	static constexpr int maxWeightFishesSpining = 3000;
};
