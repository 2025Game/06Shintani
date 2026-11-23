#ifndef  WARP_H
#define WARP_H
#include"CCharacter3.h"
#include"CEnemy1.h"
#include"CEnemy2.h"
#include"CEnemy3.h"
enum class EEnemyType
{
	ENEMY1,
	ENEMY2,
	ENEMY3,
	ENEMY4,
	ENEMY5,
	BOSS,
};

class Warp:public CCharacter3
{
public:

	Warp(EEnemyType type);
	//更新
	void Update();
	
private:
	
	//モデルのインスタンス
	static CModel msModel;
	EEnemyType mEnemyType;
	//ゲートの時間
	int gatetime;
	//ゲートが最大まで開いたかを確認する
	bool MaxGateFrag = false;
	//最大まで開いた後しばらく開いたままにするフラグ
	bool GateIdleFrag = false;
};
#endif // ! WARP_H

