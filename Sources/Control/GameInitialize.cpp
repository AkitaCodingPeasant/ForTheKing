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

    static Role Kazusa("§ö¤s¤d¯½", 30, 14);
    Kazusa.equipForce("WoodenSword");
    Kazusa.equipForce("LaurelWreath");
    Kazusa.equipForce("Bracelet");
    static Role Shiroko("¬â¯T¥Õ¤l", 34, 14);
    Shiroko.equipForce("RitualSword");
    Shiroko.equipForce("Robe");
    Shiroko.equipForce("Shoes");
    static Role Hoshino("¤p³¾´å¬P³¥", 32, 16);
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

    Kazusa.GetSkill().pushActive(SkillTable::activeMap.find("¿Pªð¡DTsubameGaeshi")->second);
    Kazusa.GetSkill().pushActive(SkillTable::activeMap.find("©Þ¤M¡DBattojutsu")->second);
    Hoshino.GetSkill().pushActive(SkillTable::activeMap.find("¿Pªð¡DTsubameGaeshi")->second);
    Hoshino.GetSkill().pushActive(SkillTable::activeMap.find("©Þ¤M¡DBattojutsu")->second);
    Shiroko.GetSkill().pushActive(SkillTable::activeMap.find("¿Pªð¡DTsubameGaeshi")->second);
    Shiroko.GetSkill().pushActive(SkillTable::activeMap.find("©Þ¤M¡DBattojutsu")->second);

    Kazusa.addItemToBackpack("®ö¤H©v¼C¡DProdigalKatana");
    Kazusa.addItemToBackpack("®ö¤H©v¼C¡DProdigalKatana");
    Kazusa.addItemToBackpack("®ö¤H©v¼C¡DProdigalKatana");

    Kazusa.renewPlayer();
    Shiroko.renewPlayer();
    Hoshino.renewPlayer();

    roles = { &Kazusa ,&Shiroko ,&Hoshino };

    sortExecutionRole();

    static Enemy EnemyA1("«°³ù¦u½Ã-¬Þ", 28, 5);
    static Enemy EnemyA2("«°³ù¦u½Ã-¼C", 26, 7);
    static Enemy EnemyA3("«°³ù¦u½Ã-Å]ªk", 24, 5);

    EnemyA1.equipForce("WoodenShield");
    EnemyA2.equipForce("WoodenSword");
    EnemyA3.equipForce("MagicWand");

    //§l¦å°­¬}¥Þ
    static Enemy EnemyB1("¥Þ©~Å]ª«", 7, 3);
    static Enemy EnemyB2("½¿½»²²ÄÝ", 5, 6);
    static Enemy EnemyB3("½¿½»²²ÄÝ", 3, 4);
    static Enemy EnemyB4("¬}¥Þ­ï§L", 13, 3);

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

    //¤£¦º±Ú¦a³ù
    static Enemy EnemyC1("¾uÅ\¦u½ÃA", 4, 10);
    static Enemy EnemyC2("¾uÅ\¦u½ÃB", 4, 11);
    static Enemy EnemyC3("¾uÅ\¦u½ÃC", 4, 12);
    static Enemy EnemyC4("ºë¾U¦u½Ã", 1, 11);
    static Enemy EnemyC5("íL«Í­ï§L", 9, 9);
    static Enemy EnemyC6("íL«Í­ï§L", 11, 15);

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

    //­ô¥¬ªL³ùÂS
    static Enemy EnemyD1("­ô¥¬ªLA", 44, 6);
    static Enemy EnemyD2("­ô¥¬ªLB", 44, 6);
    static Enemy EnemyD3("­ô¥¬ªLC", 44, 6);
    static Enemy EnemyD4("­ô¥¬ªLD", 44, 2);
    static Enemy EnemyD5("­ô¥¬ªLE", 44, 2);

    EnemyD1.GetAttribute().SetSPD(99);
    EnemyD2.GetAttribute().SetSPD(99);
    EnemyD3.GetAttribute().SetSPD(99);
    EnemyD4.GetAttribute().SetSPD(99);
    EnemyD5.GetAttribute().SetSPD(99);

    //´ËªL°Ï
    static Enemy EnemyE1("³¥¯T", 51, 15);
    static Enemy EnemyE2("³¥½ÞA", 45, 14);
    static Enemy EnemyE3("³¥½ÞB", 46, 12);
    static Enemy EnemyE4("³¥½ÞC", 46, 16);
    static Enemy EnemyE5("³¥¯T", 21, 13);
    static Enemy EnemyE6("³¥½Þ", 24, 15);
    static Enemy EnemyE7("³¥¯T", 38, 20);
    static Enemy EnemyE8("³¥½Þ", 26, 23);

    //¤ô°ì
    static Enemy EnemyF1("®ü§¯¦u½Ã", 63, 1);
    static Enemy EnemyF2("°g¸ôªº®ü§¯", 58, 2);
    static Enemy EnemyF3("®ü§¯", 55, 9);

    //¨ªÀs®l¨¦
    static Enemy EnemyG1("°g¸ôªº¨ªÀs", 65, 14);
    static Enemy EnemyG2("¨ªÀs¥®Às", 62, 19);
    static Enemy EnemyG3("¨ªÀs¥®Às", 57, 21);
    static Enemy EnemyG4("\033[31m¨ªÀs\033[0m", 55, 25);
    static Enemy EnemyG5("\033[31m¨ªÀs\033[0m", 48, 25);
    static Enemy EnemyG6("\033[31m¨ªÀs\033[0m", 59, 27);
    static Enemy EnemyG7("\033[31m¨ªÀs\033[0m", 64, 22);
    static Enemy EnemyG8("\033[31m¨ªÀs\033[0m", 61, 23);

    //³±·t¦a¨c
    static Enemy EnemyH1("¤k§Å", 22, 24);
    static Enemy EnemyH2("¨¸´c§Å®v", 19, 22);
    static Enemy EnemyH3("¥¨¼CÃM¤h", 9, 24);
    static Enemy EnemyH4("¨¸±Ð±Ð®{", 20, 27);
    static Enemy EnemyH5("´cÅ]³N¤h", 25, 27);
    static Enemy EnemyH6("¾yÅ]", 13, 21);

    //³¥¥ÍBOSS
    static Enemy Boss1("¡i±j¼Ä¡j®ö¤H¼C»¨", 4, 19); //®ö¤H©v¼C ProdigalKatana ©Þ¤M ©~¦X ¿Pªð
    static Enemy Boss2("¡i±j¼Ä¡j¦Ü´LÅ]¾É", 58, 15); //¸T§Ò¯µ¨å TabooGrimoire âf¬P ¹pÀ» Á÷­á
    static Enemy Boss3("¡i±j¼Ä¡j»È¯T", 53, 4); //»È¯T¤ò¥Ö SilverWolfFur 
    static Enemy Boss4("¡i±j¼Ä¡j«CÀs", 18, 7); //«CÀsÅìñZ DragonScaleArmor 
    static Enemy Boss5("¡i±j¼Ä¡j¼Z¸¨ªº¸tÃM¤h", 36, 5); //¸t¨~ÂêÁå SacredChain 
    static Enemy Boss6("¡i±j¼Ä¡jµLÀYÃM¤h", 35, 28); //¶A©G¬ÞµP CursedShield ¬DÆ] 

    //¥DÃDBOSS
    static Enemy BossA("¡i«Â¯Ù¡j¥¨Áè»â¥D", 26, 3); //¶Àª÷¥¨Áè GoldenHammer 
    static Enemy BossB("¡i«Â¯Ù¡j§l¦å°­", 4, 5); //·t©]©Ü­· CloakOfDarkness §l¦å 
    static Enemy BossC("¡i«Â¯Ù¡j¤£¦º±Ú¤§·½", 0, 15); //¤£¦´¹ÏÄË UndeadTotem §l¦å ¦¾¬V

    static Enemy BossD("¡i«Â¯Ù¡j­ô¥¬ªL²½¥q", 44, 2); //²½¥qÅv§ú PriestScepter âf¬P
    BossD.GetAttribute().SetSPD(99);
    BossD.equipForce("HolyGrail");
    BossD.equipForce("MagicWand");

    static Enemy BossE1("¡i«Â¯Ù¡jÅ]¤Æ³¥Ã~", 49, 9); //³¥Ã~¥Ö¤ò Animalfur 
    static Enemy BossE2("¡i«Â¯Ù¡j´Ë¤§§¯ºë", 21, 17); //¤ý¡ñ¤§°]Ä_ Gate¡ñOfBabylon
    static Enemy BossF1("¡i«Â¯Ù¡j®ü§¯¤§¤ý", 69, 3); //ºx´é¤§²´ EyeOfMaelstrom
    static Enemy BossG1("¡i«Â¯Ù¡j¿V¤§¨ªÀs", 68, 23); //¿VÀs¸t¼C FlameRetardantDragonSword
    static Enemy BossG2("¡i«Â¯Ù¡jÀs±Ú«á¸Ç", 69, 17); //Às±Ú¯µ¨÷ ScrollOfTheDragon
    static Enemy BossG3("¡i«Â¯Ù¡j¼Z¸¨±OÀsªÌ", 59, 27); //¨ªÀs¦åñZ CrimsonDragonArmor
    static Enemy BossH1("¡i«Â¯Ù¡j§Å§¯", 4, 25); //Á¶Âpªº¦Q¼Y ProfanePendant
    static Enemy BossH2("¡i«Â¯Ù¡j¥Û¹³°­", 16, 27); //´cÅ]¤§Ál WingsOfDevil

    //±bÁO
    static Tent tentA1("\033[33m¸t«°¤j¥»Àç\033[0m", 32, 14, 999);
    static Tent tentA2("\033[33m³Q¦û»âªº«°³ù\033[0m", 26, 5, 999);
    static Tent tentB("\033[31m¥Þ¦a«e­ï¯¸\033[0m", 15, 1, 999);
    static Tent tentC("\033[31m¦a³ù«e­ï¯¸\033[0m", 6, 13, 999);
    static Tent tentD("\033[32m­ô¥¬ªL±_¥Þ\033[0m", 44, 0, 999);
    static Tent tentE("\033[32m´ËªL¹i¤fÀç¦a\033[0m", 42, 14, 999);
    static Tent tentF("\033[46m²L¤ô°Ï«e­ï¯¸\033[0m", 50, 6, 999);
    static Tent tentG("\033[1m\033[35m³±·t¼éÀã¬}¥Þ\033[0m", 34, 28, 999);
    static Tent tentH("\033[33m¦a¨c­ï¯¸\033[0m", 23, 21, 999);

    static Store storeA("«°³ù°Ó©±", 32, 13);
    static Store storeB("¥Þ¦aÂø³f°Ó", 16, 1);

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
