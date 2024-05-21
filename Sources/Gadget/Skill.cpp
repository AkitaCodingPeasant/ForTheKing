#include "Skill.h"

void (* const Skill::skillTable[SKILL_TOTAL_SIZE])(void) = {
    ApplyAttack, ApplyFlee, ApplyProvoke, ApplyShockBlast,
    ApplyHeal, ApplySpeedUp, ApplyRun, ApplyHammerSplash,
    ApplyDestroy, ApplyFortify, ApplySKILL111, ApplySKILL222,
    ApplySKILL333
};

Skill::Skill()
    : skillID(0), coolDownTime(0), dice(3, 30), skillUser(nullptr), skillTargets() {}

void Skill::ApplySkill(uint8_t type, Entity* user, std::vector<Entity*> targets) {
    if (type < SKILL_TOTAL_SIZE) {
        skillTable[type]();
        skillUser = user;
        skillTargets = targets;
    }
}

void Skill::ApplyAttack() {
    // ���骺�����ޯ��@
    std::cout << "ApplyAttack called" << std::endl;
}

void Skill::ApplyFlee() {
    // ���骺�k�]�ޯ��@
    std::cout << "ApplyFlee called" << std::endl;
}

void Skill::ApplyProvoke() {
    // ���骺�D�]�ޯ��@
    std::cout << "ApplyProvoke called" << std::endl;
}

void Skill::ApplyShockBlast() {
    // ���骺�����z���ޯ��@
    std::cout << "ApplyShockBlast called" << std::endl;
}

void Skill::ApplyHeal() {
    // ���骺�v���ޯ��@
    std::cout << "ApplyHeal called" << std::endl;
}

void Skill::ApplySpeedUp() {
    // ���骺�[�t�ޯ��@
    std::cout << "ApplySpeedUp called" << std::endl;
}

void Skill::ApplyRun() {
    // ���骺�b�]�ޯ��@
    std::cout << "ApplyRun called" << std::endl;
}

void Skill::ApplyHammerSplash() {
    // ���骺�����ޯ��@
    std::cout << "ApplyHammerSplash called" << std::endl;
}

void Skill::ApplyDestroy() {
    // ���骺�����ޯ��@
    std::cout << "ApplyDestroy called" << std::endl;
}

void Skill::ApplyFortify() {
    // ���骺�j�Ƨޯ��@
    std::cout << "ApplyFortify called" << std::endl;
}

void Skill::ApplySKILL111() {
    // ���骺�۩w�q�ޯ�1��@
    std::cout << "ApplySKILL111 called" << std::endl;
}

void Skill::ApplySKILL222() {
    // ���骺�۩w�q�ޯ�2��@
    std::cout << "ApplySKILL222 called" << std::endl;
}

void Skill::ApplySKILL333() {
    // ���骺�۩w�q�ޯ�3��@
    std::cout << "ApplySKILL333 called" << std::endl;
}


void Skill::SetID(uint8_t id) {
    skillID = id;
}

uint8_t Skill::GetID() const {
    return skillID;
}
