#ifndef UI_H
#define UI_H

#include <cstdint>
#include <fstream>
#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <vector>
#include <windows.h>

#include <Attribute.h>

#include "ConstData.h"
#include "Displayer.h"
#include "Color.h"

class Dice;
class Role;
class WorldMap;
class Field;
class Store;
class Entity;
class Interactive;

namespace UI {
    using namespace Displayer;

    //std::stack<std::vector<std::vector<char>>> prevPicture;
    //WorldMap* worldMapPoac;
    //Field* fieldPointer;

    // Check whether the terminal size is big enough
    void checkConsoleSize(int, int);

    // �԰��O����l��
    void logInitialization();

    // �԰�����
    void logEvent(const std::string&);

    void logDivider(const std::string&);
    void logDivider(const std::string&, const std::string&);

    // Prepare Battle
    int PreBattle(std::vector<Enemy*>, std::vector<Role*>);

    // Display Menu
    int ShowMenu(void);

    // Display Backpack
    int Display(std::vector<std::pair<int, int>>*);

    // Display Dice
    int Display(Dice*);

    //��s�԰��������a���
    void renewPlayerInfo();

    // Display Information of Entities for Field through its ID
    int Display(Entity*);

    // Display Battle Status
    int Display(Field*);

    // Display Shops
    int Display(Store*);

    // Display Interactive Objects
    int Display(Interactive*);

    // Relocation Map to Roles�Aand Make it the Center Point Shows Part of Map
    int ReLocation(Role*);

    //���a����ت����a
    void PlayerFrame(int);
    void PlayerFrame(std::vector<int>);

    //�i��^�X�� ��l��

    // ...
};

#endif