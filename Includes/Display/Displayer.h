#ifndef DISPLAYER_H
#define DISPLAYER_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <windows.h>
#include <vector>
#include <conio.h>
#include <iomanip>

/*
#include <Enemy.h>
#include <Role.h>
*/
#include <Attribute.h>

#include <KeyBoard.h>
#include "Color.h"

class Enemy;
class Role;
class Entity;
class Active;

namespace Displayer {

    /// =========================================
    /// �H�U�O��ܻ��U�u��
    /// =========================================

    void moveCursor(int, int);

    void BuildVoid(int, int, int, int);
    void BuildFrame(int, int, int, int);
    void BuildHollowFrame(int, int, int, int);

    // ����ĳ�ϥΡA�Шϥηs�����T�Ѽ�displayFile
    void displayFile(std::ifstream&);

    void displayFile(const std::string, int, int);

    void displayString(const std::string, int, int);

    void displayString(int, int, const std::string);

    void displayChoice(std::vector<std::string>, int, int, int);

    std::string horizontalLine(const std::string, int, const char);

    std::string HpDisplayer(int, int);
    std::string FocusDisplayer(int, int);
    std::string DiceDisplayer(std::vector<int>);

    /// =========================================
    /// �H�U�O�ƭ���ܤu��
    /// =========================================

    void displayDice(std::vector<int> diceLog);
    void displayDice(int count, int focus);
    void displayPlayerInfo(int x, int y);
    void displayPlayerInfo(int x, int y, Role*);
    void displayPlayerInfo(int x, int y, Enemy*);
    void displayPlayerInfo(int x, int y, Entity*);
    void displayMiddleRectangle();
    void displayMovement();
    void displayPlayerBackpack();
    void displayPlayerStatusEffect();
    int makeChoice(std::vector<std::string>, int, int);
    void displayChoice(std::vector<Active>, int, int, int);
    std::pair<std::string, int> makeChoice(std::vector<Active>, int, int);
};

#endif