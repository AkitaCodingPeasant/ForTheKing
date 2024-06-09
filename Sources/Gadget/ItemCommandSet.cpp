#include <vector>
#include <iostream>

#include "ItemCommandSet.h"
#include "Role.h"
#include "UI.h"

void GodsbeardCommand::use(Role& role) {
	UI::logEvent(role.GetName() + "���ӤF Godsbeard �^�_�F 25 �I�ͩR�ȡC");
	role.heal(25);
}

void GoldenRootCommand::use(Role& role) {
	UI::logEvent(role.GetName() + "���ӤF GoldenRoot �^�_�F 3 �I�M�`�O�C");
	role.GetTotalAttribute().SetFocus(role.GetTotalAttribute().GetFocus() + 3);
}

void TeleportScrollCommand::use(Role& role) {
	UI::logEvent("�������ʡI�I�ګ�");
}

void TentCommand::use(Role& role) {
	UI::logEvent("�b�O�A��m�I");
}