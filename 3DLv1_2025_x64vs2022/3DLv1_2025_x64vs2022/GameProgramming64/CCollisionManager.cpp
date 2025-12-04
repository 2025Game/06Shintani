#include"CCollisionManager.h"
//マネージャーのインスタンス
CCollisionManager* CCollisionManager::mpInstance = nullptr;
//インスタンスの取得
CCollisionManager* CCollisionManager::Instance()
{
	if (mpInstance == nullptr)
	{
		mpInstance = new CCollisionManager();
	}
	return mpInstance;
}