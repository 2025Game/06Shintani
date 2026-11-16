#pragma once
#ifndef CENEMY2_E
#define CENEMY2_E

#include "CXCharacter.h"
#include"CColliderLine.h"
#include"CCollisionManager.h"
#include"CState.h"
#include"CColliderCapsule.h"
#include"CInput.h"
#include"CEnemy1Bullet.h"
#include"CGameScene.h"
#include"CXPlayer.h"
#include"CEnemyShield.h"

class CEnemy2 :public CXCharacter
{
public:
	CEnemy2(const CVector& pos, const CVector& rot = CVector(), const CVector& scale = CVector(2.5f, 2.5f, 2.5f));
	~CEnemy2();
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
	CColliderCapsule mColliderCapsule1;//カプセルコライダ
	CColliderCapsule mColliderCapsule2;//カプセルコライダ
	CColliderCapsule mColliderCapsule3;//カプセルコライダ

	CColliderCapsule mAttackRenge;//攻撃範囲のコライダ

	CInput mInput;

	bool BulletFlag = false;//弾を出したときにフラグを操作する
	bool ShieldFlag = false;//シールドがあるか判断する
	int BulletCoolTime = 0;
	//モデルのインスタンス
	static CModel msModel;
	int mHP;//HP
	int ShieldCoolTime = 0;
	CVector mPoint;	//目標地点
	CXCharacter* shield;
};
#endif // !CENEMY1_E
