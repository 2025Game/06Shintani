#include"EnemySpawner.h"
#include"Warp.h"
#include <iostream>
#define SPAWNTIME 600//生成の間隔時間


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
		
		//ワープ先でEnemy1を呼ぶ
		Warp* warp = new Warp(EEnemyType::ENEMY1);
		warp->Scale(CVector(5.0f, 5.0f, 5.0f));
		warp->Position(CVector(rand() % 150 - 150, rand() % 150 - 150, rand() % 150 - 150));
		CVector warpPos = warp->Position();
		
		//printf("Enemy1が呼ばれた:%d\n",r);
		
	}
	if (r >= 21 && r <= 40)//数字が21から40だった場合は
	{
		//ワープ先でEnemy2を呼ぶ
		Warp* warp = new Warp(EEnemyType::ENEMY2);
		warp->Scale(CVector(5.0f, 5.0f, 5.0f));
		warp->Position(CVector(rand() % 150 - 150, rand() % 150 - 150, rand() % 150 - 150));
		CVector warpPos = warp->Position();
		
		//printf("Enemy2が呼ばれた:%d\n",r);
		
	}
	if (r >= 41 && r <= 60)//数字が41から60だった場合は
	{
		//ワープ先でEnemy3を呼ぶ
		Warp* warp = new Warp(EEnemyType::ENEMY3);
		warp->Scale(CVector(5.0f, 5.0f, 5.0f));
		warp->Position(CVector(rand() % 150 - 150, rand() % 150 - 150, rand() % 150 - 150));
		CVector warpPos = warp->Position();
		
		//printf("Enemy3が呼ばれた:%d\n",r);
		
	}
	if (r >= 61 && r <= 80)//数字が61から80だった場合は
	{
		//ワープ先でEnemy4を呼ぶ
		//Warp* warp = new Warp(EEnemyType::ENEMY4);
		//warp->Scale(CVector(5.0f, 5.0f, 5.0f));
		//warp->Position(CVector(rand() % 150 - 150, rand() % 150 - 150, rand() % 150 - 150));
		//CVector warpPos = warp->Position();
		/
		//printf("Enemy4が呼ばれた:%d\n",r);
		
	}
	if (r >= 81 && r <= 100)//数字が81から100だった場合は
	{
		//ワープ先でEnemy5を呼ぶ
		//Warp* warp = new Warp(EEnemyType::ENEMY5);
		//warp->Scale(CVector(5.0f, 5.0f, 5.0f));
		//warp->Position(CVector(rand() % 150 - 150, rand() % 150 - 150, rand() % 150 - 150));
		//CVector warpPos = warp->Position();
		
		//printf("Enemy5が呼ばれた:%d\n",r);
	}
	
}

