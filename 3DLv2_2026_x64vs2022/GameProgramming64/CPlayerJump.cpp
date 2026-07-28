#include "CPlayerJump.h"
#include"CXCharacter.h"

#define GRAVITY CVector(0.0f,-0.0312f,0.0f);//重力加速度
#define JUMP_V CVector(0.0f,0.6f,0.0f)//ジャンプ初速
void CPlayerJump::Start(CXCharacter* parent)
{
	//親のポインタを保存
	mpParent = parent;
	//アニメーションの変更
	mpParent->ChangeAnimation(7, false, 60);
	mState = EState::EJUMP;//状態の種類を歩くにする
	mJumpV = JUMP_V;//ジャンプの初速度
}

void CPlayerJump::Update()
{
	//ジャンプの速度分だけ上方向へ移動させる
	mpParent->Position(mpParent->Position() + mJumpV);
	//重力加速度分だけ下方向への速度を増やす
	mJumpV = mJumpV + GRAVITY;
}

void CPlayerJump::Collision(CCollider* m, CCollider* o)
{
	//自身のコライダタイプの判定
	switch(m->Type())
	{
	case CCollider::EType::ECAPSULE://線分コライダ
		//相手のコライダが三角コライダの時
		if (o->Type() == CCollider::EType::ETRIANGLE)
		{
			CVector adjust;//調整用ベクトル
			//三角形線分の衝突判定
			if (CCollider::CollisionTriangleCapsule(o, m, &adjust))
			{
				//待機状態にする
				mState = EState::EIDLE;
			}
		}
		break;
	}
}
