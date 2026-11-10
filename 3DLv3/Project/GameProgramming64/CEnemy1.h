#pragma once
#ifndef CENEMY1_E
#define CENEMY1_E

#include "CXCharacter.h"
#include"CColliderLine.h"
#include"CCollisionManager.h"
#include"CPlayerIdle.h"
#include"CPlayerWalk.h"
#include"CPlayerAttack.h"
#include"CPlayerJump.h"
#include"CState.h"
#include"CColliderCapsule.h"
#include"CInput.h"
#include"CEnemy1Bullet.h"
#include"CGameScene.h"
#include"CXPlayer.h"

class CEnemy1 :public CXCharacter
{
public:
	CEnemy1(const CVector& pos, const CVector& rot = CVector(), const CVector& scale = CVector(2.5f, 2.5f, 2.5f));
	void Update() override;
	//衝突処理
	//Collision(コライダ１,コライダ２)
	void Collision(CCollider* m, CCollider* o);
	//衝突処理
	void Collision();

	const CMatrix& FrameCombinedMatrix(const char* name);

	void Init(CModelX* model);

	void Render() override;
private:
	CColliderLine mColliderLine;
	//EState mState;//状態の保持
	CState* mpState;//状態待機
	std::unique_ptr<CPlayerIdle> mpIdle;//待機状態
	std::unique_ptr<CPlayerWalk> mpWalk;//歩く状態
	std::unique_ptr<CPlayerAttack> mpAttack;//攻撃状態
	std::unique_ptr<CPlayerJump> mpJump;//ジャンプ状態
	CColliderCapsule mColliderCapsule1;//カプセルコライダ
	
	CColliderCapsule mAttackRenge;//攻撃範囲のコライダ
	CInput mInput;

	bool BulletFlag = false;//弾を出したときにフラグを操作する
	int BulletCoolTime = 0;
	//モデルのインスタンス
	static CModel msModel;

	int mHP;//HP

	CVector mPoint;	//目標地点

};
#endif // !CENEMY1_E
