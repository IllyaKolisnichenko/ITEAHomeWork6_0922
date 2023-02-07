#pragma once
#include<string>
#include<iostream>


class Fish {
protected:
	int maxWeigt_;
	int saturation_;
	std::string _name;
public:
	Fish(int maxWeigt, int saturation, std::string name)
	{
		maxWeigt_ = maxWeigt;
		saturation_ = saturation;
		_name = name;
	}
	int getSaturation() { return 1 + rand() % saturation_; }
	int getWeight() { return 100 + rand() % maxWeigt_; }
	std::string getSpecies() { return _name; }
};
