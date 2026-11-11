#ifndef ENEMY_SPAWNER
#define ENEMY_SPAWNER

#include "CTaskManager.h"
#include"CEnemy1.h"

class EnemySpawner :public CTaskManager
{
public:

	EnemySpawner();
	//更新
	void Update();
	//インスタンスの取得
	static EnemySpawner* Instance();
	//敵をスポーンさせる
	void Spawn();
private:
	//スポナーのインスタンス
	static EnemySpawner* mpInstance;
	int Time;//スポーン間隔
	
};

#endif // !ENEMY_SPAWNER

