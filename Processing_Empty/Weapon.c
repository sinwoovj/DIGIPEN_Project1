#include "Weapon.h"
#include "Player.h"

void InitWeaponData() {
	sword.num = 1;
	sword.range = 5;
	sword.shape = Square;
	sword.damage = 3;
	sword.isAttack = false;

	arrow.num = 2;
	arrow.range = 50;
	sword.shape = Circle;
	arrow.damage = 2;
	arrow.isAttack = false;

	wand.num = 3;
	wand.range = 0;
	sword.shape = Circle;
	wand.damage = 2;
	wand.isAttack = false;
};