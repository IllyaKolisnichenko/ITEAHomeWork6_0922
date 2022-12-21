#pragma once
#include <iostream>
#include <string>


class Waters {
public:


	static std::string getNameRiver() {
		return "River";

	}

	static std::string getNameLake() {
		return  "Lake";

	}

	static std::string getNamePond() {
		return  "Pond";

	}

	static std::string WhatIsFishRiver() {
		int f{};
		f = rand() % 100;
		if (f > 0 && f <= 40) {

			return "Carp";
		}
		if (f > 40 && f <= 80) {
			return "Crucian";
		}
		if (f > 80 && f <= 100) {
			return "Pike";

		}

	}

	static std::string WhatIsFishLake() {
		int f{};
		f = rand() % 100;
		if (f > 0 && f <= 40) {

			return "Carp";
		}
		if (f > 40 && f <= 80) {
			return "Crucian";
		}
		if (f > 80 && f <= 100) {
			return "Pike";

		}

	}

	static std::string WhatIsFishPond() {
		int f{};
		f = rand() % 100;
		if (f > 0 && f <= 3) {

			return "Carp";
		}
		if (f > 3 && f <= 10) {
			return "Crucian";
		}
		if (f > 10 && f <= 100) {
			return "FishGoby";

		}

	}
private:
};
