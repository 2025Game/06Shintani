#pragma once
#ifndef CXPLAYER_E
#define CXPLAYER_E

#include "CXCharacter.h"
#include"CColliderLine.h"
#include"CCollisionManager.h"
#include"CPlayerIdle.h"
#include"CPlayerWalk.h"
#include"CState.h"

class CXPlayer :public CXCharacter
{
public:
	CXPlayer();
	void Update() override;
	//衝突処理
	//Collision(コライダ１,コライダ２)
	void Collision(CCollider* m, CCollider* o);
	//衝突処理
	void Collision();
private:
	CColliderLine mColliderLine;
	EState mState;//状態の保持
	CState* mpState;//状態待機
	std::unique_ptr<CPlayerIdle> mpIdle;//待機状態
	std::unique_ptr<CPlayerWalk> mpWalk;//歩く状態


};
#endif // !CXPLAYER_E
