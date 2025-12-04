#pragma once
#ifndef CCOLLISIONMANAGER_H
#define CCOLLISIONMANAGER_H

#include "CTaskManager.h"

class CCollisionManager :public CTaskManager
{
public:
	//インスタンスの取得
	static CCollisionManager* Instance();
private:
	//マネージャーのインスタンス
	static CCollisionManager* mpInstance;
};
#endif // !CCOLLISIONMANAGER_H
