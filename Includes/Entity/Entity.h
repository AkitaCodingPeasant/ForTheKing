#ifndef ENTITY_H
#define ENTITY_H

#include <cstdint>
#include <vector>
#include <set>
#include <unordered_set>
#include <algorithm>
#include "Attribute.h"
#include "Skill.h"
#include "Equipment.h"
#include "EquipmentTable.h"
#include "SkillTable.h"

class Active;

class Entity {
private:
	std::string        name;            // Role Name
	Attribute          attribute;       // Attribute
	Skill              skill;           // Skill
	Equipment          equipment;	    // Equipment
	Dice               dice;            // Dice
	uint8_t            status;          // Role Status
	uint8_t            eventID;         // Current Event

public:
	Entity();
	Entity(std::string name);

	void SetName(const std::string&);
	void SetAttribute(const Attribute&);
	void SetSkill(const Skill&);
	void SetEquipment(const Equipment&);
	void SetDice(const Dice&);
	void SetStatus(const uint8_t);
	void SetEventID(const uint8_t);

	std::string         GetName(void);
	Attribute&          GetAttribute(void);
	Skill&              GetSkill(void);
	Equipment           GetEquipment(void);
	Dice&               GetDice(void);
	uint8_t             GetStatus(void);
	uint8_t             GetEventID(void);

	Attribute           GetTotalAttribute(void);
	Skill               GetTotalSkill(void);
public:
	// Find the Enemy in Range
	bool isInRange(std::vector<Entity*>);
	// Equip and UnEquip Weapon and Armor
	// �ݭn�M���~�浲�X�~�⧹��
	void equip(std::string equipmentName);
	void unEquip(std::string equipmentName);
	// �ޯ�갵
	void useSkill(std::string skillName, std::vector<Entity*> targets);
	// �p��g�L�@���p�����쪺�ˮ`(�����ǭ�l�ˮ`�i�ӴN�n)
	void takeDamage(int16_t damage, char attackType);
	// �������쪺�v���ƭ�
	void heal(int16_t heal);
};

#endif