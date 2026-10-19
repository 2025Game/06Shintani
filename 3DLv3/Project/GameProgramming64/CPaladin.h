#pragma once
#ifndef  CPALADIN_H
#define CPALADIN_H
#include"CXCharacter.h"
#include"CColliderCapsule.h"
#include"CCollisionManager.h"
#include"CState.h"
#include"CPaladinIdle.h"
#include"CPaladinDamage.h"

class CPaladin :public CXCharacter
{
public:
	//CPaladin(位置回転拡大各縮小)
	CPaladin(const CVector& pos, const CVector& rot = CVector(), const CVector& scale = CVector(2.5f, 2.5f, 2.5f));

	void Update() override;
	//Collision(コライダ１,コライダ２)
	void Collision(CCollider* m, CCollider* o);
	//衝突処理
	void Collision();
private:
	//EState mState;//状態の保持
	CState* mpState;//状態待機
	static CModelX msModel;
	CColliderCapsule mCollider;//カプセルコライダ
	std::unique_ptr<CPaladinIdle> mpIdle;//待機状態
	std::unique_ptr<CPaladinDamage> mpDamage;//ダメージ状態
	
};
#endif // ! CPALADIN_H
