#include <iostream>

#include "../../Includes/Gadget/SkillCommandSet.h"
#include "../../Includes/Gadget/SkillTable.h"

void AttackCommand::execute(Entity& caster, std::vector<Entity*> targets) {
	auto casterWeapon = caster.GetEquipment().GetWeapon();
	auto cta = caster.GetTotalAttribute();

	auto& casterDice = caster.GetDice();
	casterDice.resize(casterWeapon.GetDiceAmount());
	casterDice.SetSuccessRate(std::vector<uint8_t>(casterDice.GetAmount(), cta.GetACC()));
	casterDice.RollDice();

	int16_t damage = static_cast<int16_t>(cta.GetPA());
	std::cout << caster.GetName() << " �� Attack �z�Q�����O�� " << damage << std::endl;
	casterDice.displayResult();
	damage = static_cast<int16_t>(damage * ((double)casterDice.GetMovementPoint() / casterDice.GetAmount()));
	std::string attackType = casterWeapon.GetAttackType() == 'P' ? "���z" : "�]�k";
	std::cout << caster.GetName() << " �I��F�����O " << damage << " ��" << attackType << "�����I" << std::endl;

	targets[0]->takeDamage(damage, casterWeapon.GetAttackType());
}

void FleeCommand::execute(Entity& caster, std::vector<Entity*> targets) {
	auto cta = caster.GetTotalAttribute();

	auto& casterDice = caster.GetDice();
	casterDice.resize(1);
	uint8_t successRate = static_cast<uint8_t>((double)cta.GetHP() * (cta.GetSPD()) * 100 / (cta.GetMaxHP() + cta.GetMD() + cta.GetPD()));
	successRate = successRate > 98 ? 98 : successRate;
	std::cout << caster.GetName() << " �����\�k�]���v�� " << (unsigned)successRate << "%" << std::endl;
	casterDice.SetSuccessRate(std::vector<uint8_t>(1, successRate));
	casterDice.RollDice();
	casterDice.displayResult();

	if (casterDice.GetMovementPoint() == 1) {
		std::cout << caster.GetName() << " �k�]���\�I�I" << std::endl;
		// ctargets[0]->SetStatus(�k�]���A);
	} else {
		std::cout << caster.GetName() << " �k�]���ѡA�~�򧤨c�C" << std::endl;
	}
}

void ProvokeCommand::execute(Entity& caster, std::vector<Entity*> targets) {
	auto cta = caster.GetTotalAttribute();
	
	auto& casterDice = caster.GetDice();
	casterDice.resize(1);
	uint8_t successRate = static_cast<uint8_t>((double)cta.GetHP() / ((cta.GetMaxHP() + cta.GetMD() + cta.GetPA())));
	casterDice.SetSuccessRate(std::vector<uint8_t>(1, successRate));
	std::cout << caster.GetName() << " �� Provoke ���\���v�� " << (unsigned)successRate << "%" << std::endl;
	casterDice.RollDice();
	casterDice.displayResult();

	if (casterDice.GetAmount() == 1) {
		std::cout << "�D�]���\�A�{�b " << targets[0]->GetName() << " �ܷQ�� " << caster.GetName() << " �z�F�@�y�C" << std::endl;
		// targets[0]->SetStatus(�D�]���A);
	} else {
		std::cout << "�D�]���ѡA" << targets[0]->GetName() << "�u��" << caster.GetName() << " ��p���C" << std::endl;
	}
}

void ShockBlastCommand::execute(Entity& caster, std::vector<Entity*> targets) {
	auto casterWeapon = caster.GetEquipment().GetWeapon();
	auto cta = caster.GetTotalAttribute();

	auto& casterDice = caster.GetDice();
	casterDice.resize(3);
	casterDice.SetSuccessRate(std::vector<uint8_t>(3, cta.GetACC() - 5));
	casterDice.RollDice();

	int16_t damage = static_cast<int16_t>((double)((double)cta.GetMA() / 2));
	std::cout << caster.GetName() << " �� ShockBlast �z�Q�����O�� " << damage << std::endl;
	casterDice.displayResult();
	damage = static_cast<int16_t>((double)((double)cta.GetMA() / 2) * ((double)casterDice.GetMovementPoint() / casterDice.GetAmount()));
	std::string attackType = casterWeapon.GetAttackType() == 'P' ? "���z" : "�]�k";
	std::cout << caster.GetName() << " �����ĤH�I��F " << damage << " ��" << attackType << "�����I" << std::endl;
	for (auto target : targets) {
		target->takeDamage(damage, casterWeapon.GetAttackType());
	}
}

void HealCommand::execute(Entity& caster, std::vector<Entity*> targets) {
	auto cta = caster.GetTotalAttribute();

	auto& casterDice = caster.GetDice();
	casterDice.resize(3);
	casterDice.SetSuccessRate(std::vector<uint8_t>(3, cta.GetACC()));
	casterDice.RollDice();

	int16_t heal = static_cast<int16_t>((double)cta.GetMA() * 1.5);
	std::cout << caster.GetName() << " �� Heal �z�Q�v���q�� " << heal << std::endl;
	casterDice.displayResult();
	heal = static_cast<int16_t>(heal * ((double)casterDice.GetMovementPoint() / casterDice.GetAmount()));
	std::cout << caster.GetName() << " �� "<< targets[0]->GetName() << " �I��F " << heal << " ���v���I" << std::endl;
	targets[0]->heal(heal);
}

void SpeedUpCommand::execute(Entity& caster, std::vector<Entity*> targets) {
	auto cta = caster.GetTotalAttribute();

	auto& casterDice = caster.GetDice();
	casterDice.resize(2);
	casterDice.SetSuccessRate(std::vector<uint8_t>(2, cta.GetACC()));
	std::cout << caster.GetName() << " �� Speed Up ���\���v�� " << (unsigned)cta.GetACC() << "%" << std::endl;
	casterDice.RollDice();

	if (casterDice.GetMovementPoint() == 2) {
		std::cout << caster.GetName() << " �� Speed Up ���\�I���� " << targets[0]->GetName() << " 1�^�X�� SpeedUp Buff�C" << std::endl;
		// ����SpeedUp Buff�@�^�X
		Buff SpeedUp = SkillTable::buffMap.find("SpeedUp")->second;
		targets[0]->GetSkill().pushBuff(SpeedUp);
	} else {
		std::cout << caster.GetName() << " �� Speed Up ���ѡI" << std::endl;
	}
}