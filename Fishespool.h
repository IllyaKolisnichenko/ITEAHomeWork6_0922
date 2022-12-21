#pragma once
#include<string>
#include<iostream>


class Fishes {

public:


protected:
	static constexpr int maxWeigt_{ 5000 };
	static constexpr int saturation_{ 10 };



};

class Carps : public Fishes {

private:
	std::string species_;
public:
	Carps()
		:species_{ "Carp" }

	{

	}

	static int getWeight() {
		return 100 + rand() % maxWeigt_;

	}
	static int getSaturation() {
		return 1 + rand() % saturation_;

	}

	std::string getSpecies() {
		return species_;

	}


};


class Crucians : public Fishes {

private:
	static std::string species_;
public:
	Crucians()
	{
		std::string species_ = "Crucian";
	}

	int getWeight() {
		return 100 + rand() % maxWeigt_;

	}
	int getSaturation() {
		return 1 + rand() % saturation_;

	}

	static std::string getSpecies() {
		return species_;

	}



};


class Pikes : public Fishes {

private:
	static std::string species_;
public:
	Pikes()
	{
		std::string species{ "Pike" };
	}

	int getWeight() {
		return 100 + rand() % maxWeigt_;

	}
	int getSaturation() {
		return 1 + rand() % saturation_;

	}

	static std::string getSpecies() {
		return species_;

	}



};

class FishGoby : public Fishes {

private:
	std::string species_;
	static constexpr int maxWeightGoby_ = 500;
public:
	FishGoby()
		:species_{ "FishGoby" }

	{

	}

	static int getWeight() {
		return 100 + rand() % maxWeightGoby_;

	}
	static int getSaturation() {
		return 1 + rand() % saturation_;

	}

	std::string getSpecies() {
		return species_;

	}


};

