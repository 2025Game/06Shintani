#pragma once
#ifndef CXPLAYER_E
#define CXPLAYER_E

#include "CXCharacter.h"
#include"CColliderLine.h"
#include"CCollisionManager.h"
#include"CPlayerIdle.h"
#include"CPlayerWalk.h"
#include"CPlayerAttack.h"
#include"CPlayerJump.h"
#include"CState.h"
#include"CColliderCapsule.h"

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
	
	const CMatrix& FrameCombinedMatrix(const char* name);

	void Init(CModelX* model);
private:
	CColliderLine mColliderLine;
	//EState mState;//状態の保持
	CState* mpState;//状態待機
	std::unique_ptr<CPlayerIdle> mpIdle;//待機状態
	std::unique_ptr<CPlayerWalk> mpWalk;//歩く状態
	std::unique_ptr<CPlayerAttack> mpAttack;//攻撃状態
	std::unique_ptr<CPlayerJump> mpJump;//ジャンプ状態
	CColliderCapsule mColliderCapsule;//カプセルコライダ
	CColliderCapsule mColliderSword;//カプセルコライダ

};
#endif // !CXPLAYER_E
