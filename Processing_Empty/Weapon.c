#include "Weapon.h"

void InitWeaponData() {
	sword.num = 1;
	sword.range = 50;
	sword.damage = 5;
	sword.isAttack = false;

	arrow.num = 2;
	arrow.range = 50;
	arrow.damage = 5;
	arrow.isAttack = false;

	wand.num = 3;
	wand.range = 0;
	wand.damage = 5;
	wand.isAttack = false;
};