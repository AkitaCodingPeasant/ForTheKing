#ifndef CHEST_H
#define CHEST_H

#include <cstdint>
#include <fstream>
#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <vector>
#include <windows.h>

#include <Interactive.h>

class Role;

class Chest : public Interactive {

private:
    std::pair<uint32_t, uint32_t> position;
    std::string name = "隨機寶箱";
    std::vector<std::string> treasures;
public:
    Chest();
    Chest(int x, int y);
    Chest(int x, int y, std::string name, std::vector<std::string> treasures);
public:
    void SetPosition(const std::pair<uint32_t, uint32_t>&);
    std::pair<uint32_t, uint32_t> GetPosition() const;

    std::string GetName() { return name; }

    // Give Item or Money to Role
    void GiveTreasureTo(Role*);


};

#endif