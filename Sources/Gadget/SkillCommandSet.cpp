#include <SkillCommandSet.h>
#include <SkillTable.h>
#include "SkillCommand.h"
#include <UI.h>
#include <Dice.h>
#include "Entity.h"

void AttackActiveCommand::execute(Entity& caster, std::vector<Entity*> targets, uint8_t coolDown, uint8_t tick, uint8_t diceAmount) {
    auto casterWeapon = caster.GetEquipment().GetWeapon();
    auto cta = caster.GetTotalAttribute();
    int16_t damage = casterWeapon.GetAttackType() == 'P' ? static_cast<int16_t>(cta.GetPA()) : static_cast<int16_t>(cta.GetMA());
    UI::logEvent(caster.GetName() + " 的 Attack 理想攻擊力為 " + std::to_string(damage));
    targets[0]->SetlastDamage(damage);

    auto& casterDice = caster.GetDice();
    casterDice.resize(casterWeapon.GetDiceAmount());
    casterDice.SetSuccessRate(std::vector<uint8_t>(casterDice.GetAmount(), cta.GetACC()));
    casterDice.RollDice();
    casterDice.displayResult();
    damage = static_cast<int16_t>(damage * ((double)casterDice.GetMovementPoint() / casterDice.GetAmount()));
    std::string attackType = casterWeapon.GetAttackType() == 'P' ? "物理" : "魔法";

    UI::logEvent(caster.GetName() + " 施放了攻擊力 " + std::to_string(damage) + " 的" + attackType + "攻擊！");

    targets[0]->takeDamage(damage, casterWeapon.GetAttackType());
}

void FleeActiveCommand::execute(Entity& caster, std::vector<Entity*> targets, uint8_t coolDown, uint8_t tick, uint8_t diceAmount) {
    auto cta = caster.GetTotalAttribute();

    auto& casterDice = caster.GetDice();
    casterDice.resize(diceAmount);
    uint8_t successRate = static_cast<uint8_t>((double)cta.GetHP() * (cta.GetSPD()) / (cta.GetMaxHP() + cta.GetMD() + cta.GetPD()));
    successRate = successRate > 98 ? 98 : successRate;
    UI::logEvent(caster.GetName() + " 的成功逃跑機率為 " + std::to_string((unsigned)successRate) + "%");

    casterDice.SetSuccessRate(std::vector<uint8_t>(1, successRate));
    casterDice.RollDice();
    casterDice.displayResult();

    if (casterDice.GetMovementPoint() == 1) {
        UI::logEvent(caster.GetName() + " 逃跑成功！！");
        targets[0]->SetStatus(targets[0]->GetStatus() | RETREAT);
    }
    else {
        UI::logEvent(caster.GetName() + " 逃跑失敗，繼續坐牢。");
    }
}

void ProvokeActiveCommand::execute(Entity& caster, std::vector<Entity*> targets, uint8_t coolDown, uint8_t tick, uint8_t diceAmount) {
    auto cta = caster.GetTotalAttribute();

    auto& casterDice = caster.GetDice();
    casterDice.resize(diceAmount);
    uint8_t successRate = static_cast<uint8_t>(1, (double)cta.GetHP() / ((cta.GetMaxHP() + cta.GetMD() + cta.GetPA())) * 100);
    casterDice.SetSuccessRate(std::vector<uint8_t>(1, successRate));
    UI::logEvent(caster.GetName() + " 的 Provoke 成功機率為 " + std::to_string((unsigned)successRate) + "%");
    casterDice.RollDice();
    casterDice.displayResult();
    targets[0]->SetlastDamage(0);

    if (casterDice.GetMovementPoint() == 1) {
        UI::logEvent("挑釁成功，現在 " + targets[0]->GetName() + " 很躁。");
        targets[0]->addBuff("Angry", 3);
    }
    else {
        UI::logEvent("挑釁失敗，" + targets[0]->GetName() + " 只把 " + caster.GetName() + " 當小丑。");
    }
}

void ShockBlastActiveCommand::execute(Entity& caster, std::vector<Entity*> targets, uint8_t coolDown, uint8_t tick, uint8_t diceAmount) {
    auto casterWeapon = caster.GetEquipment().GetWeapon();
    auto cta = caster.GetTotalAttribute();

    auto& casterDice = caster.GetDice();
    casterDice.resize(diceAmount);
    casterDice.SetSuccessRate(std::vector<uint8_t>(diceAmount, cta.GetACC() - 5));
    casterDice.RollDice();
    int16_t damage = static_cast<int16_t>((double)((double)cta.GetMA() / 2));
    UI::logEvent(caster.GetName() + " 的 ShockBlast 理想攻擊力為 " + std::to_string(damage));

    casterDice.displayResult();
    damage = static_cast<int16_t>((double)((double)cta.GetMA() / 2) * ((double)casterDice.GetMovementPoint() / casterDice.GetAmount()));
    std::string attackType = casterWeapon.GetAttackType() == 'P' ? "物理" : "魔法";

    UI::logEvent(caster.GetName() + " 對全體敵人施放了 " + std::to_string(damage) + " 的" + attackType + "攻擊！");

    bool perfect = casterDice.GetAmount() == casterDice.GetMovementPoint();
    if (perfect)
        UI::logEvent("完美擲骰，敵人全體受到內傷");
    for (auto target : targets) {
        target->takeDamage(damage, casterWeapon.GetAttackType());
        // 中毒好怪
        if (perfect)
            target->addBuff("Poisoned", 2);
    }
}

void HealActiveCommand::execute(Entity& caster, std::vector<Entity*> targets, uint8_t coolDown, uint8_t tick, uint8_t diceAmount) {
    auto cta = caster.GetTotalAttribute();

    auto& casterDice = caster.GetDice();
    casterDice.resize(diceAmount);
    casterDice.SetSuccessRate(std::vector<uint8_t>(diceAmount, cta.GetACC()));
    casterDice.RollDice();

    int16_t heal = static_cast<int16_t>((double)cta.GetMA() * 1.5);
    UI::logEvent(caster.GetName() + " 的 Heal 理想治療量為 " + std::to_string(heal));
    casterDice.displayResult();
    heal = static_cast<int16_t>(heal * ((double)casterDice.GetMovementPoint() / casterDice.GetAmount()));
    UI::logEvent(caster.GetName() + " 對 " + targets[0]->GetName() + " 施放了 " + std::to_string(heal) + " 的治療！");
    targets[0]->heal(heal);
}

void SpeedUpActiveCommand::execute(Entity& caster, std::vector<Entity*> targets, uint8_t coolDown, uint8_t tick, uint8_t diceAmount) {
    auto cta = caster.GetTotalAttribute();

    auto& casterDice = caster.GetDice();
    casterDice.resize(diceAmount);
    casterDice.SetSuccessRate(std::vector<uint8_t>(diceAmount, cta.GetACC()));
    casterDice.RollDice();

    if (casterDice.GetMovementPoint() == 2) {
        UI::logEvent(caster.GetName() + " 的 Speed Up 成功！");
        // 給予SpeedUp Buff一回合
        targets[0]->addBuff("SpeedUp", 1);
    }
    else {
        UI::logEvent(caster.GetName() + " 的 Speed Up 失敗！");
    }
}

// 燕返
void TsubameGaeshiActiveCommand::execute(Entity& caster, std::vector<Entity*> targets, uint8_t coolDown, uint8_t tick, uint8_t diceAmount) {
    auto cta = caster.GetTotalAttribute();
    int16_t damage1 = static_cast<int16_t>(cta.GetPA() / 2);
    int16_t damage2 = static_cast<int16_t>((cta.GetPA()) + (cta.GetMA()) / 3);
    int16_t damage3 = static_cast<int16_t>((cta.GetPA()) + (cta.GetMA()) / 2);
    UI::logEvent(caster.GetName() + " 擺起了 燕返 的架式，理想攻擊力為 " + std::to_string(damage1 + damage2 + damage3));

    auto& casterDice = caster.GetDice();
    casterDice.resize(diceAmount);
    casterDice.SetSuccessRate(std::vector<uint8_t>(casterDice.GetAmount(), cta.GetACC()));
    casterDice.RollDice();
    casterDice.displayResult();

    damage1 = static_cast<int16_t>(damage1 * ((double)casterDice.GetMovementPoint() / casterDice.GetAmount()));
    damage2 = static_cast<int16_t>(damage2 * ((double)casterDice.GetMovementPoint() / casterDice.GetAmount()));
    damage3 = static_cast<int16_t>(damage3 * ((double)casterDice.GetMovementPoint() / casterDice.GetAmount()));


    UI::logEvent(caster.GetName() + " 揮出了第一刀 " + std::to_string(damage1) + " 傷害的物理攻擊！");
    targets[0]->takeDamage(damage1, 'P');
    UI::renewPlayerInfo();
    Sleep(500);
    UI::logEvent(caster.GetName() + " 揮出了第二刀 " + std::to_string(damage2) + " 傷害的物魔混傷攻擊！");
    targets[0]->takeDamage(damage2, 'X');
    UI::renewPlayerInfo();
    Sleep(500);
    UI::logEvent(caster.GetName() + " 揮出了第三刀 " + std::to_string(damage3) + " 傷害的無視防禦攻擊！");
    targets[0]->takeDamage(damage3, 'I');
}

// 拔刀
void BattojutsuActiveCommand::execute(Entity& caster, std::vector<Entity*> targets, uint8_t coolDown, uint8_t tick, uint8_t diceAmount) {
    auto cta = caster.GetTotalAttribute();
    int16_t damage = static_cast<int16_t>(cta.GetPA());
    UI::logEvent(caster.GetName() + " 手緊握著劍柄，理想攻擊力為 " + std::to_string(damage));

    auto& casterDice = caster.GetDice();
    casterDice.resize(diceAmount);
    casterDice.SetSuccessRate(std::vector<uint8_t>(casterDice.GetAmount(), cta.GetACC() * 1.35));
    casterDice.RollDice();
    casterDice.displayResult();

    damage = static_cast<int16_t>(damage * ((double)casterDice.GetMovementPoint() / casterDice.GetAmount()));
    UI::logEvent(caster.GetEquipment().GetWeapon().GetName() + " 出鞘，斬出 " + std::to_string(damage) + " 物理傷害！");
    targets[0]->takeDamage(damage, 'P');

    bool perfect = casterDice.GetAmount() == casterDice.GetMovementPoint();
    if (perfect) {
        UI::renewPlayerInfo();
        UI::logEvent(caster.GetName() + " 揮出完美的一擊，追加第二段收刀傷害");
        UI::logEvent(caster.GetName() + " 追加暈眩效果");
        targets[0]->takeDamage(damage, 'P');
        targets[0]->addBuff("Dizziness", 1);
    }
}

//雷擊
void ThunderboltActiveCommand::execute(Entity& caster, std::vector<Entity*> targets, uint8_t coolDown, uint8_t tick, uint8_t diceAmount) {
    auto cta = caster.GetTotalAttribute();
    int16_t damage = static_cast<int16_t>(cta.GetMA());
    UI::logEvent(caster.GetName() + " 被靛紫色的光點圍繞，理想攻擊力為 " + std::to_string(damage));

    auto& casterDice = caster.GetDice();
    casterDice.resize(diceAmount);
    casterDice.SetSuccessRate(std::vector<uint8_t>(casterDice.GetAmount(), cta.GetACC()));
    casterDice.RollDice();
    casterDice.displayResult();

    damage = static_cast<int16_t>(damage * ((double)casterDice.GetMovementPoint() / casterDice.GetAmount()));
    UI::logEvent("轟雷擊發，對全體敵人造成 " + std::to_string(damage) + " 魔法傷害！");

    bool perfect = casterDice.GetAmount() == casterDice.GetMovementPoint();
    if (perfect) {
        UI::logEvent("完美施法 追加效果");
    } 
    for (auto target : targets) {
        target->takeDamage(damage, 'M');
        // 中毒好怪
        if (perfect)
            target->addBuff("Poisoned", 3);
    }
}

//霜凜
void FreezeActiveCommand::execute(Entity& caster, std::vector<Entity*> targets, uint8_t coolDown, uint8_t tick, uint8_t diceAmount) {
    auto cta = caster.GetTotalAttribute();
    int16_t damage = static_cast<int16_t>(cta.GetMA()) * 0.8;
    UI::logEvent("冰霜在 " + caster.GetName() + " 手中蔓延，理想攻擊力為 " + std::to_string(damage));

    auto& casterDice = caster.GetDice();
    casterDice.resize(diceAmount);
    casterDice.SetSuccessRate(std::vector<uint8_t>(casterDice.GetAmount(), cta.GetACC()));
    casterDice.RollDice();
    casterDice.displayResult();

    damage = static_cast<int16_t>(damage * ((double)casterDice.GetMovementPoint() / casterDice.GetAmount()));
    UI::logEvent("冰霜將敵方凍結，對全體敵人造成 " + std::to_string(damage) + " 魔法傷害！");

    bool perfect = casterDice.GetAmount() == casterDice.GetMovementPoint();
    for (auto target : targets) {
        target->takeDamage(damage, 'M');
    }
    if (perfect) {
        UI::logEvent("完美施法，冰霜迸裂追加效果");
        for (auto target : targets) {

            target->takeDamage(damage * 0.5, 'M');
            target->addBuff("Dizziness", 1);
        }
    }
}

//火殞
void InfernoActiveCommand::execute(Entity& caster, std::vector<Entity*> targets, uint8_t coolDown, uint8_t tick, uint8_t diceAmount) {
    auto cta = caster.GetTotalAttribute();
    int16_t damage = static_cast<int16_t>(cta.GetMA()) * 1.2;
    UI::logEvent(caster.GetName() + " 的身邊被火星纏繞，理想攻擊力為 " + std::to_string(damage));

    auto& casterDice = caster.GetDice();
    casterDice.resize(diceAmount);
    casterDice.SetSuccessRate(std::vector<uint8_t>(casterDice.GetAmount(), cta.GetACC()));
    casterDice.RollDice();
    casterDice.displayResult();

    damage = static_cast<int16_t>(damage * ((double)casterDice.GetMovementPoint() / casterDice.GetAmount()));
    UI::logEvent("烈焰噴發，對全體敵人造成 " + std::to_string(damage) + " 魔法傷害！");

    bool perfect = casterDice.GetAmount() == casterDice.GetMovementPoint();
    for (auto target : targets) {
        target->takeDamage(damage, 'M');
    }
}

//威壓
void CoercionActiveCommand::execute(Entity& caster, std::vector<Entity*> targets, uint8_t coolDown, uint8_t tick, uint8_t diceAmount) {
    auto cta = caster.GetTotalAttribute();

    auto& casterDice = caster.GetDice();
    std::string str = cta.GetMD() > cta.GetPD() ? "魔力" : "鬥氣";
    UI::logEvent(caster.GetName() + " 凝聚" + str + "，成功機率為 " + std::to_string(cta.GetACC()) + " % ");

    casterDice.resize(diceAmount);
    casterDice.SetSuccessRate(std::vector<uint8_t>(casterDice.GetAmount(), cta.GetACC()));
    casterDice.RollDice();
    casterDice.displayResult();

    bool perfect = casterDice.GetAmount() == casterDice.GetMovementPoint();
    if (perfect) {
        UI::logEvent("威壓成功");
        for (auto target : targets) {
            target->addBuff("Angry", 1);
        }
    }
    else {
        UI::logEvent("威壓失敗");
    }
}

//劍氣
void SwordBeamActiveCommand::execute(Entity& caster, std::vector<Entity*> targets, uint8_t coolDown, uint8_t tick, uint8_t diceAmount) {
    /*
    auto cta = caster.GetTotalAttribute();
    int16_t damage1 = static_cast<int16_t>(cta.GetPA());
    int16_t damage2 = static_cast<int16_t>(cta.GetPA() + cta.GetMA());

    UI::logEvent("魔力纏繞在 " + caster.GetName() + "手中的武器");
    UI::logEvent("理想攻擊力為 " + std::to_string(damage1 + damage2));

    auto& casterDice = caster.GetDice();
    casterDice.resize(diceAmount);
    casterDice.SetSuccessRate(std::vector<uint8_t>(casterDice.GetAmount(), cta.GetACC() * 1.25));
    casterDice.RollDice();
    casterDice.displayResult();

    damage1 = static_cast<int16_t>(damage1 * ((double)casterDice.GetMovementPoint() / casterDice.GetAmount()));
    damage2 = static_cast<int16_t>(damage2 * ((double)casterDice.GetMovementPoint() / casterDice.GetAmount()));

    UI::logEvent(caster.GetEquipment().GetWeapon().GetName() + " 出鞘，斬出 " + std::to_string(damage) + " 物理傷害！");
    targets[0]->takeDamage(damage, 'P');

    bool perfect = casterDice.GetAmount() == casterDice.GetMovementPoint();
    if (perfect) {
        UI::renewPlayerInfo();
        UI::logEvent(caster.GetName() + " 揮出完美的一擊，追加第二段收刀傷害");
        UI::logEvent(caster.GetName() + " 追加暈眩效果");
        targets[0]->takeDamage(damage, 'P');
        targets[0]->addBuff("Dizziness", 1);
    }
    */
}

//Passive

void RunPassiveCommand::execute(Entity& caster, std::vector<Entity*> targets) {
    if (targets[0]->GetDice().GetFocusCount() == 0) {
        targets[0]->GetDice().SetFocusCount(1);
        UI::logEvent(caster.GetName() + " 的被動 Run 被觸發，第一個擲骰保證成功！");
    }
}

void HammerSplashPassiveCommand::execute(Entity& caster, std::vector<Entity*> targets) {
    UI::logEvent(caster.GetName() + " 的被動 HammerSplash 被觸發！");
    targets[0]->addBuff("Dizziness", 1);
    for (int i = 1; i < targets.size(); i++) {
        if (targets[i]->GetStatus() & RETREAT || targets[i]->GetStatus() & DEAD)
            continue;

        targets[i]->takeDamage(targets[0]->GetlastDamage() * 0.5, 'P');
    }
}

void DestroyPassiveCommand::execute(Entity& caster, std::vector<Entity*> targets) {
    UI::logEvent(caster.GetName() + " 的被動 Destroy 被觸發！");
    // 現在沒有人可以觸發 Destroy，所以這邊就先不寫，留時間給其他東西
}

void FortifyPassiveCommand::execute(Entity& caster, std::vector<Entity*> targets) {
    // Fortify 不應該在這裡被觸發，而是要在Entity::takeDamage()裡面被觸發
    UI::logEvent(caster.GetName() + " 的被動 Fortify 被觸發！所受傷害自動 * 0.9");
}

//Buff

void AngryBuffCommand::execute(Entity& caster) {
    UI::logEvent(caster.GetName() + " 很氣，氣到骰子都骰不好了@@");
    caster.GetDice().SetRateAddition(std::vector<double>(caster.GetDice().GetAmount(), -30));
}

void DizzinessBuffCommand::execute(Entity& caster) {
    UI::logEvent(caster.GetName() + " 被 Dizziness 了");
}

void PoisonedBuffCommand::execute(Entity& caster) {
    UI::logEvent(caster.GetName() + " 因為 Poisoned 所以受到了持續傷害");
    int16_t damage = static_cast<int16_t>(caster.GetTotalAttribute().GetHP() * 0.1);
    damage = damage == 0 ? 1 : damage;
    caster.takeTrueDamage(damage);
}

void SpeedUpBuffCommand::execute(Entity& caster) {
    UI::logEvent(caster.GetName() + " 的速度提升了 50% !");
    caster.GetTotalAttribute().SetSPD((caster.GetTotalAttribute().GetSPD() + 0.5) * 1.5);
    UI::renewPlayerInfo();
}

void SpeedUpBuffDeConstructCommand::execute(Entity& caster) {
    // UI::logEvent(caster.GetName() + " 的 SpeedUp 沒了。");
    caster.GetTotalAttribute().SetSPD(caster.GetTotalAttribute().GetSPD() / 1.5);
    UI::renewPlayerInfo();
}

void AngryBuffDeConstructCommand::execute(Entity& caster) {
    UI::logEvent(caster.GetName() + " 不 Angry 了，體悟心靈祥和。");
    caster.GetDice().SetRateAddition(std::vector<double>(caster.GetDice().GetAmount(), 0));
}