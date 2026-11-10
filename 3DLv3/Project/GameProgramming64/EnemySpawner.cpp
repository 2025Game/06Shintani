#include"EnemySpawner.h"

#include <iostream>

#define SPAWNTIME 240//生成の間隔時間
//スポナーのインスタンス
EnemySpawner* EnemySpawner::mpInstance = nullptr;

EnemySpawner::EnemySpawner()
	:Time(SPAWNTIME)
{
}
// インスタンスの取得
EnemySpawner * EnemySpawner::Instance()
{
	if (mpInstance == nullptr)
	{
		mpInstance = new EnemySpawner();
		//printf("追加");
	}
	return mpInstance;
}

void EnemySpawner::Update()
{
	if (Time <= 0)
	{
		Spawn();
		Time = SPAWNTIME;
		//printf("敵がスポーンした");
	}

	Time--;
}

void EnemySpawner::Spawn()
{
	int r= rand() % 99+1;//1～100のランダムな数字を呼び出す

	if (r >= 1 && r <= 20)//数字が1から20だった場合は
	{
		//Enemy1を呼ぶ
		// //エネミー１のインスタンスを生成
		CXCharacter* enemy1 = new CEnemy1(CVector(0.0f, 0.0f, 0.0f));
		enemy1->Position(CVector(rand()%150-150, rand() % 150 - 150, rand() % 150 - 150));
		//printf("Enemy1が呼ばれた:%d\n",r);
	}
	if (r >= 21 && r <= 40)//数字が21から40だった場合は
	{
		//Enemy2を呼ぶ
		//printf("Enemy2が呼ばれた:%d\n",r);
	}
	if (r >= 41 && r <= 60)//数字が41から60だった場合は
	{
		//Enemy3を呼ぶ
		//printf("Enemy3が呼ばれた:%d\n",r);
	}
	if (r >= 61 && r <= 80)//数字が61から80だった場合は
	{
		//Enemy4を呼ぶ
		//printf("Enemy4が呼ばれた:%d\n",r);
	}
	if (r >= 81 && r <= 100)//数字が81から100だった場合は
	{
		//Enemy5を呼ぶ
		//printf("Enemy5が呼ばれた:%d\n",r);
	}
	
}
