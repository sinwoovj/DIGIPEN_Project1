#include "EnemyAttack.h"
#include "Player.h"
#include "cprocessing.h"

const float WindowWidthHalf = 960;
const float WindowHeightHalf = 540;

void EnemyCloseAttack1() // 한방향
{
	// 플레이어 위치를 기준으로 방향을 결정해서 공격함
	// x를 먼저 windowWidth / 2를 기준으로 큰지 작은지 나누고 그다음 y순
	if (player.coord.x >= WindowWidthHalf)
	{

	}
}
void EnemyCloseAttack2() // 수직 수평
{
	// 한방향과 같이 x를 먼저 중앙을 기준으로 나누고 만약 y가 중앙을 기준으로 보스 크기 /2 위아래를 넘어서면 수평으로 반대일 경우 수평으로 공격한다.

}
void EnemyCloseAttack3() // 전방향
{
	// 모든 방향, 그냥 네모라고 생각하면 된다.

}

void EnemyProjectileRandomAttack1()
{

}
void EnemyProjectileRandomAttack2()
{

}
void EnemyProjectileRandomAttack3()
{

}

void EnemyPatternAttack1()
{

}
void EnemyPatternAttack2()
{

}
void EnemyPatternAttack3()
{

}
