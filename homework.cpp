#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <map>



using namespace std;

struct Fish
{
    string name;
    int max_weight{};
    int min_weight{};

};

struct Lake
{
    string name;
    int cost{};
    int extension_cost{};
    vector<Fish*> fish;
    map<string, int> bait;
};

class Fisherman
{
private:
    string name;
    int money;
    int fishing_time;

    int current_weight;

public:
    Lake *current_lake;
    string current_bait;
    Fisherman(string name, int money)
            : name(std::move(name)), money(money), fishing_time(0), current_lake(nullptr), current_weight(0) {}

    void setCurrentLake(Lake *lake)
    {
        current_lake = lake;
    }

    void setCurrentBait(string bait)
    {
        current_bait = std::move(bait);
    }

    void fish()
    {
        if (current_lake == nullptr)
        {
            cout << "Select the lake first!" << endl;
            return;
        }

        if (current_bait.empty())
        {
            cout << "Set the bait first!" << endl;
            return;
        }

        if (fishing_time < 20)
        {
            cout << "Your time is over!" << endl;
            cout << "If you want to continue, extend your time!" << endl;
            return;
        }

        fishing_time -= 20;
        int probability = current_lake->bait[current_bait];
        int luck = rand() % 10 + 1;
        int frequency = 0;
        Fish caught_fish;
        for (auto &fish : current_lake->fish)
        {
            if (probability > luck)
            {
                frequency++;
                caught_fish = *fish;
            }
        }


        if (frequency == 0)
        {
            cout << "The fish did not jump on the bait." << endl;
            return;
        }

        int chosen_fish = rand() % frequency + 1;
        int i= 0;
        for (auto &fish : current_lake->fish)
        {
            if (probability > luck)
            {
                i++;
                if (i == chosen_fish)
                {
                    int weight_of_fish = (rand() % (fish->max_weight - fish->min_weight)) + fish->min_weight;
                    current_weight += weight_of_fish;
                    cout << "you caught a fish '" << fish->name << "' weighing " << weight_of_fish << " kg!\n" << endl;
                    break;
                }
            }
        }
    }
    void leaveFishingPlace()
    {
        if (current_weight == 0)
        {
            cout << "You didn't catch anything.\n" << endl;
            return;
        }

        cout << "You've earned " << current_weight/10 << " hrn.\n" << endl;
        money += current_weight/10;
        current_weight = 0;
        current_lake = nullptr;
        current_bait = "";
    }


    void showInfo()
    {
        cout << "Fisherman's name: " << name << endl;
        cout << "Balance: " << money << " hrn." << endl;
        cout << "Fishing time: " << fishing_time << " minutes" << endl;
        if (current_lake != nullptr)
        {
            cout << "Current lake: " << current_lake->name << endl;
            cout << "Current bait: " << current_bait << endl;
        }
        else
        {
            cout << "You are not at the fishing spot." << endl;
        }
        cout << "Current catch: " << current_weight << " kg\n" << endl;
    }

    bool pay(int amount)
    {
        if (money < amount)
        {
            cout << "Insufficient funds on the account.\n" << endl;
            return false;
        }

        money -= amount;
        fishing_time = 180;
        return true;
    }

    bool extendFishingTime()
    {
        if (current_lake == nullptr)
        {
            cout << "Choose a lake first!\n" << endl;
            return false;
        }

        if (!pay(current_lake->extension_cost))
        {
            return false;
        }

        fishing_time += 180;
        return true;
    }
};

const string &R(const string& basicString);

void readFish(const string& filename, vector<Fish> &fishes)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Cant open file!" << endl;
        return;
    }

    while (!file.eof())
    {
        Fish fish;
        file >> fish.name >> fish.max_weight;
        fishes.push_back(fish);
    }

    file.close();
}


void readLakes(const string& filename, vector<Lake> &lakes, vector<Fish> &fish) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Cant open the file!" << endl;
        return;
    }

    while (!file.eof()) {
        Lake lake;
        file >> lake.name >> lake.cost >> lake.extension_cost;
        int fish_count;
        file >> fish_count;
        for (int i = 0; i < fish_count; i++) {
            string fish_name;
            file >> fish_name;
            Fish *current_fish = nullptr;
            for (auto & j : fish) {
                if (j.name == fish_name) {
                    current_fish = &j;
                    break;
                }
            }
            lake.fish.push_back(current_fish);
        }
        int bait_count;
        file >> bait_count;
        for (int i = 0; i < bait_count; i++) {
            string bait;
            int chance;
            file >> bait;
            file >> chance;
            lake.bait[bait] = chance;
        }
        lakes.push_back(lake);
    }
    file.close();
}

enum Actions{
    CastFishingRod = 1,
    ChangeBait,
    SellFishes,
    ChangeLake,
    CurrentCatch,
    ExtendTime,
    Exit
};


int main()
{
    string file_fishes;
    string file_lakes;


    cout << "Specify the path to the fish information file\n";
    cout << "Like C:/Users/Denis/Downloads/fishes.txt\n";
    cin >> file_fishes;
    cout << "Specify the path to the fish information file\n";
    cout << "Like C:/Users/Denis/Downloads/lakes.txt\n";
    cin >> file_lakes;

    vector<Fish> fish;
    readFish(file_fishes, fish);
    vector<Lake> lakes;
    readLakes(file_lakes, lakes, fish);


    string name;
    int money;
    cout << "Enter the name of the fisherman: ";
    cin >> name;
    cout << "Enter opening balance: ";
    cin >> money;
    Fisherman fisherman(name, money);

    while (true) {
        cout << "\nSelect an action:" << endl;
        cout << "1. Cast a fishing rod" << endl;
        cout << "2. Change bait" << endl;
        cout << "3. Sell the fishes and leave the lake" << endl;
        cout << "4. Change lake" << endl;
        cout << "5. Information about the current catch" << endl;
        cout << "6. Extend fishing time" << endl;
        cout << "7. Exit" << endl;
        int choice;
        cin >> choice;

        string bait_choice;

        if (choice == Actions::CastFishingRod)
            fisherman.fish();

        else if (choice == Actions::ChangeBait) {
            if (fisherman.current_lake == nullptr) {
                cout << "Choose a lake first!\n" << endl;
                continue;
            }

            cout << "Available baits: " << endl;
            for (auto &item: fisherman.current_lake->bait) {
                cout << item.first << endl;
            }
            cout << "Type name of bait: \n";

            cin >> bait_choice;
            try {
                fisherman.setCurrentBait(fisherman.current_lake->bait.find(bait_choice)->first);
            }
            catch (bad_alloc) {
                cout << "Type name, not number!!\n" << endl;
            }
        }

        else if (choice == Actions::SellFishes)
            fisherman.leaveFishingPlace();


        else if (choice == Actions::ChangeLake) {
            cout << "Accessible lakes: " << endl;
            for (int i = 0; i < lakes.size(); i++) {
                cout << i + 1 << ". " << lakes[i].name << endl;
            }

            cout << "Select lake: ";
            int lake_choice;
            cin >> lake_choice;
            if (!fisherman.pay(lakes[lake_choice - 1].cost)) {
                continue;
            }
            fisherman.setCurrentLake(&lakes[lake_choice - 1]);
        }

        else if (choice == Actions::CurrentCatch)
                fisherman.showInfo();


        else if (choice == Actions::ExtendTime)
            fisherman.extendFishingTime();

        else if (choice == Actions::Exit)
            return 0;

        else
            cout << "Incorrect choice." << endl;
        }
    }

    
