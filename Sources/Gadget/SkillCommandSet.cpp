#include "../../Includes/Gadget/SkillCommandSet.h"

void AttackCommand::execute(Entity& caster, std::vector<Entity*> targets, uint8_t coolDown, uint8_t tick, uint8_t diceAmount) {
    auto casterWeapon = caster.GetEquipment().GetWeapon();
    auto cta = caster.GetTotalAttribute();

    int16_t damage = static_cast<int16_t>(cta.GetPA());
    UI::logEvent(caster.GetName() + " �� Attack �z�Q�����O�� " + std::to_string(damage));

    auto& casterDice = caster.GetDice();
    casterDice.resize(casterWeapon.GetDiceAmount());
    casterDice.SetSuccessRate(std::vector<uint8_t>(casterDice.GetAmount(), cta.GetACC()));
    casterDice.RollDice();
    casterDice.displayResult();
    damage = static_cast<int16_t>(damage * ((double)casterDice.GetMovementPoint() / casterDice.GetAmount()));
    std::string attackType = casterWeapon.GetAttackType() == 'P' ? "���z" : "�]�k";

    UI::logEvent(caster.GetName() + " �I��F�����O " + std::to_string(damage) + " ��" + attackType + "�����I");

    targets[0]->takeDamage(damage, casterWeapon.GetAttackType());
}

void FleeCommand::execute(Entity& caster, std::vector<Entity*> targets, uint8_t coolDown, uint8_t tick, uint8_t diceAmount) {
    auto cta = caster.GetTotalAttribute();

    auto& casterDice = caster.GetDice();
    casterDice.resize(diceAmount);
    uint8_t successRate = static_cast<uint8_t>((double)cta.GetHP() * (cta.GetSPD()) * 100 / (cta.GetMaxHP() + cta.GetMD() + cta.GetPD()));
    successRate = successRate > 98 ? 98 : successRate;
    UI::logEvent(caster.GetName() + " �����\�k�]���v�� " + std::to_string((unsigned)successRate) + "%");

    casterDice.SetSuccessRate(std::vector<uint8_t>(1, successRate));
    casterDice.RollDice();
    casterDice.displayResult();

    if (casterDice.GetMovementPoint() == 1) {
        UI::logEvent(caster.GetName() + " �k�]���\�I�I");
        // ctargets[0]->SetStatus(�k�]���A);
    } else {
        UI::logEvent(caster.GetName() + " �k�]���ѡA�~�򧤨c�C");
    }
}

void ProvokeCommand::execute(Entity& caster, std::vector<Entity*> targets, uint8_t coolDown, uint8_t tick, uint8_t diceAmount) {
    auto cta = caster.GetTotalAttribute();

    auto& casterDice = caster.GetDice();
    casterDice.resize(diceAmount);
    uint8_t successRate = static_cast<uint8_t>(1, (double)cta.GetHP() / ((cta.GetMaxHP() + cta.GetMD() + cta.GetPA())) * 100);
    casterDice.SetSuccessRate(std::vector<uint8_t>(1, successRate));
    UI::logEvent(caster.GetName() + " �� Provoke ���\���v�� " + std::to_string((unsigned)successRate) + "%");
    casterDice.RollDice();
    casterDice.displayResult();

    if (casterDice.GetMovementPoint() == 1) {
        UI::logEvent("�D�]���\�A�{�b " + targets[0]->GetName() + " �ܷQ�� " + caster.GetName() + " �z�F�@�y�C");
        // targets[0]->SetStatus(�D�]���A);
    } else {
        UI::logEvent("�D�]���ѡA" + targets[0]->GetName() + "�u��" + caster.GetName() + " ��p���C");
    }
}

void ShockBlastCommand::execute(Entity& caster, std::vector<Entity*> targets, uint8_t coolDown, uint8_t tick, uint8_t diceAmount) {
    auto casterWeapon = caster.GetEquipment().GetWeapon();
    auto cta = caster.GetTotalAttribute();

    auto& casterDice = caster.GetDice();
    casterDice.resize(diceAmount);
    casterDice.SetSuccessRate(std::vector<uint8_t>(3, cta.GetACC() - 5));
    casterDice.RollDice();

    int16_t damage = static_cast<int16_t>((double)((double)cta.GetMA() / 2));
    UI::logEvent(caster.GetName() + " �� ShockBlast �z�Q�����O�� " + std::to_string(damage));

    casterDice.displayResult();
    damage = static_cast<int16_t>((double)((double)cta.GetMA() / 2) * ((double)casterDice.GetMovementPoint() / casterDice.GetAmount()));
    std::string attackType = casterWeapon.GetAttackType() == 'P' ? "���z" : "�]�k";

    UI::logEvent(caster.GetName() + " �����ĤH�I��F " + std::to_string(damage) + " ��" + attackType + "�����I");
    for (auto target : targets) {
        target->takeDamage(damage, casterWeapon.GetAttackType());
    }
}

void HealCommand::execute(Entity& caster, std::vector<Entity*> targets, uint8_t coolDown, uint8_t tick, uint8_t diceAmount) {
    auto cta = caster.GetTotalAttribute();

    auto& casterDice = caster.GetDice();
    casterDice.resize(diceAmount);
    casterDice.SetSuccessRate(std::vector<uint8_t>(3, cta.GetACC()));
    casterDice.RollDice();

    int16_t heal = static_cast<int16_t>((double)cta.GetMA() * 1.5);
    UI::logEvent(caster.GetName() + " �� Heal �z�Q�v���q�� " + std::to_string(heal));
    casterDice.displayResult();
    heal = static_cast<int16_t>(heal * ((double)casterDice.GetMovementPoint() / casterDice.GetAmount()));
    UI::logEvent(caster.GetName() + " �� " + targets[0]->GetName() + " �I��F " + std::to_string(heal) + " ���v���I");
    targets[0]->heal(heal);
}

void SpeedUpCommand::execute(Entity& caster, std::vector<Entity*> targets, uint8_t coolDown, uint8_t tick, uint8_t diceAmount) {
    auto cta = caster.GetTotalAttribute();

    auto& casterDice = caster.GetDice();
    casterDice.resize(diceAmount);
    casterDice.SetSuccessRate(std::vector<uint8_t>(2, cta.GetACC()));
    UI::logEvent(caster.GetName() + " �� Speed Up ���\���v�� " + std::to_string((unsigned)cta.GetACC()) + "%");
    casterDice.RollDice();

    if (casterDice.GetMovementPoint() == 2) {
        UI::logEvent(caster.GetName() + " �� Speed Up ���\�I");
        UI::logEvent("���� " + targets[0]->GetName() + " 1�^�X�� SpeedUp Buff�C");
        // ����SpeedUp Buff�@�^�X
        Buff SpeedUp = SkillTable::buffMap.find("SpeedUp")->second;
        targets[0]->GetSkill().pushBuff(SpeedUp);
    }
    else {
        UI::logEvent(caster.GetName() + " �� Speed Up ���ѡI");
    }
}