#include"Warp.h"

#define MODEL_WARP "res\\Gate\\Gate.obj","res\\Gate\\Gate.mtl"
#define GATE_TIME 120 //ゲートが完全に開くまでの時間
#define GATE_IDLETIME 120 //ゲートが完全に開いてから閉じるまでの時間

//静的メンバ変数の定着
CModel Warp::msModel;

Warp::Warp(EEnemyType type)
	:gatetime(0)
	,mEnemyType(type)
{
	//モデルデータがなければ読み込み
	if (msModel.Triangles().empty())
	{
		msModel.Load(MODEL_WARP);
	}
	//モデルポインタの設定
	mpModel = &msModel;
	
}

void Warp::Update()
{
	if (MaxGateFrag == false)
	{
		if (GATE_TIME >= gatetime)
		{
			//ゲートが最大まで開いていなかったら広げる
			mScale = mScale + CVector(0.05f, 0.05f, 0.05f);
			gatetime++;

		}
		else
		{
			switch (mEnemyType)
			{
			case EEnemyType::ENEMY1:
			{
				CEnemy1* enemy = new CEnemy1(CVector(0.0f, 0.0f, 0.0f));
				enemy->Position(mPosition);
				MaxGateFrag = true;
				gatetime = 0;
				break;
			}

			case EEnemyType::ENEMY2:
			{
				CEnemy2* enemy = new CEnemy2(CVector(0.0f, 0.0f, 0.0f));
				enemy->Position(mPosition);
				MaxGateFrag = true;
				gatetime = 0;
				break;
			}

			case EEnemyType::ENEMY3:
			{
				CEnemy3* enemy = new CEnemy3(CVector(0.0f, 0.0f, 0.0f));
				enemy->Position(mPosition);
				MaxGateFrag = true;
				gatetime = 0;
				break;
			}
			case EEnemyType::ENEMY4:
			{

				MaxGateFrag = true;
				gatetime = 0;
				break;
			}
			case EEnemyType::ENEMY5:
			{

				MaxGateFrag = true;
				gatetime = 0;
				break;
			}
			case EEnemyType::BOSS:
			{

				MaxGateFrag = true;
				gatetime = 0;
				break;
			}

			return;
			}
		}


	}
	else
	{
		if (GateIdleFrag == false)
		{
			//ゲートが最大まで開いたら2秒間開いたままにする
			if (GATE_IDLETIME>= gatetime)
			{
				gatetime++;
			}
			else
			{
				gatetime = 0;
				GateIdleFrag = true;
			}
		}
		if (GateIdleFrag == true)
		{
			//ゲートが最大まで開いたら閉じて消えるようにする
			if (GATE_TIME / 2 >= gatetime)
			{
				//ゲートが最大まで開いていなかったら広げる
				mScale = mScale + CVector(-0.1f, -0.1f, -0.1f);
				gatetime++;

			}
			else
			{
				mEnabled = false;
			}
		}
		
	}
	
	CTransform::Update();
	mRotation = mRotation + (CVector(0.0f, 0.0f, 1.0f));
}