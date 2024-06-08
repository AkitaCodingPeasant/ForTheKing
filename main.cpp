#include "Includes/Entity/Role.h"
#include "Includes/Entity/Enemy.h"
#include "Includes/Gadget/Equipment.h"
#include "Includes/Gadget/EquipmentTable.h"
#include "Includes/Gadget/SkillTable.h"
#include "Includes/Display/UI.h"
#include <Process.h>

#include <string>

int main() {
    SkillTable::Initialize();
    EquipmentTable::Initialize();

    UI::checkConsoleSize(50, 180);
    UI::ShowMenu();
    //ui.makeChoice({"FUCKOOP","FUCK�����","FUCK��Ͷ�"}, 50,20);

    system("Pause");
    system("CLS");

    Role hero("hero");
    Enemy dragon("dragon");

    Role profPao("�j����");
    Role myWife("��T�դl�ڱC");
    Enemy porfDai("�����");
    Enemy tonya("Tonya");

    hero.equip("MagicWand");
    profPao.equip("Hammer");
    myWife.equip("RitualSword");

    profPao.GetAttribute().SetMaxFocus(20);
    profPao.GetAttribute().SetFocus(20);

    //system("Pause");


    Process::HandlePreBattle({ &dragon , &porfDai  , &tonya }, { &hero ,&profPao  , &myWife });

    //UI::PreBattle({ &dragon , &porfDai  , &tonya }, { &hero ,&profPao  , &myWife });
    UI::moveCursor(2, 9);


    std::vector<Entity*> targets;
    targets.push_back(&dragon);
    for (int i = 0; i < 5; i++) {
        auto skills = hero.GetTotalSkill().GetActive();
        std::string skillToUse = UI::makeChoice(skills, 6, 9).first;
        UI::logDivider(skillToUse);
        hero.useActive(skillToUse, { &dragon });
    }

    UI::logDivider("");
    hero.GetDice().SetFocusCount(3);
    hero.useActive("Attack", { &dragon });
    UI::logDivider("");
    hero.useActive("Flee", { &hero });
    UI::logDivider("");
    hero.useActive("ShockBlast", { &dragon });
    UI::logDivider("");
    hero.useActive("Heal", { &hero });
    UI::logDivider("");
    hero.useActive("Heal", { &dragon });
    UI::logDivider("");

    UI::logDivider("Equip WoodenSword");
    hero.equip("WoodenSword");
    hero.useActive("SpeedUp", { &hero });

    UI::logDivider("Hero");
    hero.GetTotalAttribute();
    UI::logDivider("Dragon");
    dragon.GetTotalAttribute();


    UI::logDivider("Equip Equipment");
    hero.equip("GiantHammer");
    hero.equip("LaurelWreath");
    hero.equip("HolyGrail");

    //hero.GetTotalAttribute().display();
    //std::cout << std::endl;

    UI::logDivider("Apply Skill");
    //hero.GetTotalSkill().display();

    //���Ʃw�q
    //std::vector<Entity*> targets;
    //targets.push_back(&dragon);

    UI::logDivider("1");
    hero.useActive("Attack", targets);
    UI::logDivider("2");
    hero.useActive("Attack", targets);
    UI::logDivider("3");
    hero.useActive("Attack", targets);
    UI::logDivider("4");
    hero.useActive("Attack", targets);
    UI::logDivider("5");
    hero.useActive("Attack", targets);
    UI::logDivider("6");
    hero.useActive("Attack", targets);
    UI::logDivider("7");
    hero.useActive("Attack", targets);
    UI::logDivider("8");
    hero.useActive("Flee", targets);
    UI::logDivider("9");
    hero.useActive("Heal", targets);
    UI::logDivider("10");
    //hero.useActive("SpeedUp", targets);

    UI::logDivider("UnEquip Equipment");
    hero.unEquip(hero.GetEquipment().GetWeapon().GetName());
    hero.unEquip(hero.GetEquipment().GetArmor().GetName());
    hero.unEquip(hero.GetEquipment().GetAccessory().GetName());
    hero.useActive("Attack", targets);
    hero.useActive("Flee", targets);
    //hero.useActive("Heal", targets);
    //hero.useActive("SpeedUp", targets);
    UI::logDivider("Hero");
    //hero.GetTotalAttribute().display();
    UI::logDivider("Dragon");
    //dragon.GetTotalAttribute().display();
    //std::cout << std::endl;


    return 0;
}
