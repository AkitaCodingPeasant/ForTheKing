#include <WorldMap.h>
#include <Role.h>
#include <Game.h>
#include <Enemy.h>
#include <WorldMap.h>
#include <Role.h>
#include <KeyBoard.h>
#include <EquipmentTable.h>
#include "Dice.h"
#include "Color.h"
#include "Field.h"
#include "EquipmentTable.h"
#include "ItemTable.h"
#include "Tent.h"
#include "Chest.h"
#include "Store.h"
#include "Backpack.h"
#include "Item.h"
#include "SkillTable.h"

void Game::Initialize() {
    SkillTable::Initialize();
    EquipmentTable::Initialize();
    ItemTable::Initialize();

    static Role Kazusa("���s�d��", 30, 14);
    Kazusa.equipForce("WoodenSword");
    Kazusa.equipForce("LaurelWreath");
    Kazusa.equipForce("Bracelet");
    static Role Shiroko("��T�դl", 34, 14);
    Shiroko.equipForce("RitualSword");
    Shiroko.equipForce("Robe");
    Shiroko.equipForce("Shoes");
    static Role Hoshino("�p����P��", 32, 16);
    Hoshino.equipForce("Hammer");
    Hoshino.equipForce("PlateArmor");
    Hoshino.equipForce("HolyGrail");

    Kazusa.GetAttribute().SetMaxFocus(5);
    Kazusa.GetAttribute().SetFocus(5);
    Kazusa.GetAttribute().SetSPD(70);
    Shiroko.GetAttribute().SetMaxFocus(5);
    Shiroko.GetAttribute().SetFocus(5);
    Shiroko.GetAttribute().SetSPD(70);
    Hoshino.GetAttribute().SetMaxFocus(5);
    Hoshino.GetAttribute().SetFocus(5);
    Hoshino.GetAttribute().SetSPD(70);

    Kazusa.addItemToBackpack("Tent");
    Kazusa.addItemToBackpack("Tent");
    Kazusa.addItemToBackpack("Tent");
    Kazusa.addItemToBackpack("Godsbeard");
    Kazusa.addItemToBackpack("Godsbeard");
    Kazusa.addItemToBackpack("Godsbeard");
    Kazusa.addItemToBackpack("GoldenRoot");
    Kazusa.addItemToBackpack("GoldenRoot");
    Kazusa.addItemToBackpack("GoldenRoot");
    Kazusa.addItemToBackpack("TeleportScroll");
    Kazusa.addItemToBackpack("TeleportScroll");
    Kazusa.addItemToBackpack("TeleportScroll");

    Kazusa.GetSkill().pushActive(SkillTable::activeMap.find("�P��DTsubameGaeshi")->second);
    Kazusa.GetSkill().pushActive(SkillTable::activeMap.find("�ޤM�DBattojutsu")->second);
    Hoshino.GetSkill().pushActive(SkillTable::activeMap.find("�P��DTsubameGaeshi")->second);
    Hoshino.GetSkill().pushActive(SkillTable::activeMap.find("�ޤM�DBattojutsu")->second);
    Shiroko.GetSkill().pushActive(SkillTable::activeMap.find("�P��DTsubameGaeshi")->second);
    Shiroko.GetSkill().pushActive(SkillTable::activeMap.find("�ޤM�DBattojutsu")->second);

    Kazusa.addItemToBackpack("���H�v�C�DProdigalKatana");
    Kazusa.addItemToBackpack("���H�v�C�DProdigalKatana");
    Kazusa.addItemToBackpack("���H�v�C�DProdigalKatana");

    Kazusa.renewPlayer();
    Shiroko.renewPlayer();
    Hoshino.renewPlayer();

    roles = { &Kazusa ,&Shiroko ,&Hoshino };

    sortExecutionRole();

    static Enemy EnemyA1("�����u��-��", 28, 5);
    static Enemy EnemyA2("�����u��-�C", 26, 7);
    static Enemy EnemyA3("�����u��-�]�k", 24, 5);

    EnemyA1.equipForce("WoodenShield");
    EnemyA2.equipForce("WoodenSword");
    EnemyA3.equipForce("MagicWand");

    //�l�尭�}��
    static Enemy EnemyB1("�ީ~�]��", 7, 3);
    static Enemy EnemyB2("��������", 5, 6);
    static Enemy EnemyB3("��������", 3, 4);
    static Enemy EnemyB4("�}�ޭ�L", 13, 3);

    EnemyB1.equipForce("Hammer");
    EnemyB1.GetAttribute().SetMaxHP(99);
    EnemyB1.GetAttribute().SetHP(99);
    EnemyB1.GetAttribute().SetPA(10);
    EnemyB1.GetAttribute().SetPD(10);
    EnemyB1.GetAttribute().SetACC(20);
    EnemyB1.GetAttribute().SetSPD(20);
    EnemyB1.renewPlayer();
    EnemyB2.GetAttribute().SetMaxHP(20);
    EnemyB2.GetAttribute().SetHP(20);
    EnemyB3.GetAttribute().SetMaxHP(20);
    EnemyB3.GetAttribute().SetHP(20);

    //�����ڦa��
    static Enemy EnemyC1("�u�\�u��A", 4, 10);
    static Enemy EnemyC2("�u�\�u��B", 4, 11);
    static Enemy EnemyC3("�u�\�u��C", 4, 12);
    static Enemy EnemyC4("��U�u��", 1, 11);
    static Enemy EnemyC5("�L�ͭ�L", 9, 9);
    static Enemy EnemyC6("�L�ͭ�L", 11, 15);

    EnemyC1.GetAttribute().SetPA(10);
    EnemyC1.equipForce("LeatherArmor");
    EnemyC2.GetAttribute().SetPA(10);
    EnemyC2.equipForce("LeatherArmor");
    EnemyC3.GetAttribute().SetPA(10);
    EnemyC3.equipForce("LeatherArmor");
    EnemyC4.GetAttribute().SetSPD(25);
    EnemyC4.GetAttribute().SetPA(30);
    EnemyC4.equipForce("GiantHammer");
    EnemyC5.equipForce("Shoes");
    EnemyC5.equipForce("RitualSword");
    EnemyC6.equipForce("Shoes");
    EnemyC6.equipForce("RitualSword");

    //�����L���S
    static Enemy EnemyD1("�����LA", 44, 6);
    static Enemy EnemyD2("�����LB", 44, 6);
    static Enemy EnemyD3("�����LC", 44, 6);
    static Enemy EnemyD4("�����LD", 44, 2);
    static Enemy EnemyD5("�����LE", 44, 2);

    EnemyD1.GetAttribute().SetSPD(99);
    EnemyD2.GetAttribute().SetSPD(99);
    EnemyD3.GetAttribute().SetSPD(99);
    EnemyD4.GetAttribute().SetSPD(99);
    EnemyD5.GetAttribute().SetSPD(99);

    //�˪L��
    static Enemy EnemyE1("���T", 51, 15);
    static Enemy EnemyE2("����A", 45, 14);
    static Enemy EnemyE3("����B", 46, 12);
    static Enemy EnemyE4("����C", 46, 16);
    static Enemy EnemyE5("���T", 21, 13);
    static Enemy EnemyE6("����", 24, 15);
    static Enemy EnemyE7("���T", 38, 20);
    static Enemy EnemyE8("����", 26, 23);

    //����
    static Enemy EnemyF1("�����u��", 63, 1);
    static Enemy EnemyF2("�g��������", 58, 2);
    static Enemy EnemyF3("����", 55, 9);

    //���s�l��
    static Enemy EnemyG1("�g�������s", 65, 14);
    static Enemy EnemyG2("���s���s", 62, 19);
    static Enemy EnemyG3("���s���s", 57, 21);
    static Enemy EnemyG4("\033[31m���s\033[0m", 55, 25);
    static Enemy EnemyG5("\033[31m���s\033[0m", 48, 25);
    static Enemy EnemyG6("\033[31m���s\033[0m", 59, 27);
    static Enemy EnemyG7("\033[31m���s\033[0m", 64, 22);
    static Enemy EnemyG8("\033[31m���s\033[0m", 61, 23);

    //���t�a�c
    static Enemy EnemyH1("�k��", 22, 24);
    static Enemy EnemyH2("���c�Ův", 19, 22);
    static Enemy EnemyH3("���C�M�h", 9, 24);
    static Enemy EnemyH4("���бЮ{", 20, 27);
    static Enemy EnemyH5("�c�]�N�h", 25, 27);
    static Enemy EnemyH6("�y�]", 13, 21);

    //����BOSS
    static Enemy Boss1("�i�j�ġj���H�C��", 4, 19); //���H�v�C ProdigalKatana �ޤM �~�X �P��
    static Enemy Boss2("�i�j�ġj�ܴL�]��", 58, 15); //�T�ү��� TabooGrimoire �f�P �p�� ����
    static Enemy Boss3("�i�j�ġj�ȯT", 53, 4); //�ȯT��� SilverWolfFur 
    static Enemy Boss4("�i�j�ġj�C�s", 18, 7); //�C�s���Z DragonScaleArmor 
    static Enemy Boss5("�i�j�ġj�Z�����t�M�h", 36, 5); //�t�~���� SacredChain 
    static Enemy Boss6("�i�j�ġj�L�Y�M�h", 35, 28); //�A�G�޵P CursedShield �D�] 

    //�D�DBOSS
    static Enemy BossA("�i�¯١j�����D", 26, 3); //�������� GoldenHammer 
    static Enemy BossB("�i�¯١j�l�尭", 4, 5); //�t�]�ܭ� CloakOfDarkness �l�� 
    static Enemy BossC("�i�¯١j�����ڤ���", 0, 15); //�������� UndeadTotem �l�� ���V

    static Enemy BossD("�i�¯١j�����L���q", 44, 2); //���q�v�� PriestScepter �f�P
    BossD.GetAttribute().SetSPD(99);
    BossD.equipForce("HolyGrail");
    BossD.equipForce("MagicWand");

    static Enemy BossE1("�i�¯١j�]�Ƴ��~", 49, 9); //���~�֤� Animalfur 
    static Enemy BossE2("�i�¯١j�ˤ�����", 21, 17); //���񤧰]�_ Gate��OfBabylon
    static Enemy BossF1("�i�¯١j��������", 69, 3); //�x�餧�� EyeOfMaelstrom
    static Enemy BossG1("�i�¯١j�V�����s", 68, 23); //�V�s�t�C FlameRetardantDragonSword
    static Enemy BossG2("�i�¯١j�s�ګ��", 69, 17); //�s�گ��� ScrollOfTheDragon
    static Enemy BossG3("�i�¯١j�Z���O�s��", 59, 27); //���s���Z CrimsonDragonArmor
    static Enemy BossH1("�i�¯١j�ŧ�", 4, 25); //���p���Q�Y ProfanePendant
    static Enemy BossH2("�i�¯١j�۹���", 16, 27); //�c�]���l WingsOfDevil

    //�b�O
    static Tent tentA1("\033[33m�t���j����\033[0m", 32, 14, 999);
    static Tent tentA2("\033[33m�Q���⪺����\033[0m", 26, 5, 999);
    static Tent tentB("\033[31m�ަa�e�ﯸ\033[0m", 15, 1, 999);
    static Tent tentC("\033[31m�a���e�ﯸ\033[0m", 6, 13, 999);
    static Tent tentD("\033[32m�����L�_��\033[0m", 44, 0, 999);
    static Tent tentE("\033[32m�˪L�i�f��a\033[0m", 42, 14, 999);
    static Tent tentF("\033[46m�L���ϫe�ﯸ\033[0m", 50, 6, 999);
    static Tent tentG("\033[1m\033[35m���t����}��\033[0m", 34, 28, 999);
    static Tent tentH("\033[33m�a�c�ﯸ\033[0m", 23, 21, 999);

    static Store storeA("�����ө�", 32, 13);
    static Store storeB("�ަa���f��", 16, 1);

    static Chest chestA1(3, 6);

    roles = { &Kazusa ,&Shiroko ,&Hoshino };
    //stores = { &storeA };
    //enemys = {  };
    //tents = { &tentA1 ,&tentA2 };
    chests = { &chestA1 };

    WorldMap::SetTents(tents);
    WorldMap::SetRoles(roles);
    WorldMap::SetEnemys(enemys);
    WorldMap::SetStores(stores);
    WorldMap::SetChests(chests);

    WorldMap::loadMap("map.txt");

    return;
}
