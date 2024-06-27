#ifndef SKILLCOMMANDSET_H
#define SKILLCOMMANDSET_H

#include <vector>
#include <iostream>

#include <SkillCommand.h>

class Entity;

class AttackActiveCommand : public SkillCommand {
public:
    void execute(Entity& caster, std::vector<Entity*> target, uint8_t coolDown, uint8_t tick, uint8_t diceAmount) override;
};

class FleeActiveCommand : public SkillCommand {
public:
	void execute(Entity& caster, std::vector<Entity*> target, uint8_t coolDown, uint8_t tick, uint8_t diceAmount) override;
};

class ProvokeActiveCommand : public SkillCommand {
public:
	void execute(Entity& caster, std::vector<Entity*> target, uint8_t coolDown, uint8_t tick, uint8_t diceAmount) override;
};

class ShockBlastActiveCommand : public SkillCommand {
public:
	void execute(Entity& caster, std::vector<Entity*> target, uint8_t coolDown, uint8_t tick, uint8_t diceAmount) override;
};

class HealActiveCommand : public SkillCommand {
public:
	void execute(Entity& caster, std::vector<Entity*> target, uint8_t coolDown, uint8_t tick, uint8_t diceAmount) override;
};

class SpeedUpActiveCommand : public SkillCommand {
public:
	void execute(Entity& caster, std::vector<Entity*> target, uint8_t coolDown, uint8_t tick, uint8_t diceAmount) override;
};
//燕返
class TsubameGaeshiActiveCommand : public SkillCommand {
public:
	void execute(Entity& caster, std::vector<Entity*> target, uint8_t coolDown, uint8_t tick, uint8_t diceAmount) override;
};
//拔刀
class BattojutsuActiveCommand : public SkillCommand {
public:
	void execute(Entity& caster, std::vector<Entity*> target, uint8_t coolDown, uint8_t tick, uint8_t diceAmount) override;
};
//雷擊
class ThunderboltActiveCommand : public SkillCommand {
public:
	void execute(Entity& caster, std::vector<Entity*> target, uint8_t coolDown, uint8_t tick, uint8_t diceAmount) override;
};
//霜凜
class FreezeActiveCommand : public SkillCommand {
public:
	void execute(Entity& caster, std::vector<Entity*> target, uint8_t coolDown, uint8_t tick, uint8_t diceAmount) override;
};

//火殞
class InfernoActiveCommand : public SkillCommand {
public:
	void execute(Entity& caster, std::vector<Entity*> target, uint8_t coolDown, uint8_t tick, uint8_t diceAmount) override;
};

//威壓
class CoercionActiveCommand : public SkillCommand {
public:
	void execute(Entity& caster, std::vector<Entity*> target, uint8_t coolDown, uint8_t tick, uint8_t diceAmount) override;
};

//掃射
class SparyActiveCommand : public SkillCommand {
public:
	void execute(Entity& caster, std::vector<Entity*> target, uint8_t coolDown, uint8_t tick, uint8_t diceAmount) override;
};

//劍氣
class SwordBeamActiveCommand : public SkillCommand {
public:
	void execute(Entity& caster, std::vector<Entity*> target, uint8_t coolDown, uint8_t tick, uint8_t diceAmount) override;
};


class RunPassiveCommand : public SkillCommand {
public:
	void execute(Entity& caster, std::vector<Entity*> target) override;
};

class HammerSplashPassiveCommand : public SkillCommand {
public:
	void execute(Entity& caster, std::vector<Entity*> target) override;
};

class DestroyPassiveCommand : public SkillCommand {
public:
	void execute(Entity& caster, std::vector<Entity*> target) override;
};

class FortifyPassiveCommand : public SkillCommand {
public:
	void execute(Entity& caster, std::vector<Entity*> target) override;
};

class AngryBuffCommand : public SkillCommand {
public:
	void execute(Entity& caster) override;
};

class DizzinessBuffCommand : public SkillCommand {
public:
	void execute(Entity& caster) override;
};

class PoisonedBuffCommand : public SkillCommand {
public:
	void execute(Entity& caster) override;
};

class SpeedUpBuffCommand : public SkillCommand {
public:
	void execute(Entity& caster) override;
};

class AngryBuffDeConstructCommand : public SkillCommand {
public:
	void execute(Entity& caster) override;
};

class SpeedUpBuffDeConstructCommand : public SkillCommand {
public:
	void execute(Entity& caster) override;
};

#endif
