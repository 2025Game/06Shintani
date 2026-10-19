#include "CPlayerAttack.h"
#include"CXCharacter.h"

void CPlayerAttack::Start(CXCharacter* parent)
{
	//親のポインタを保存
	mpParent = parent;
	//アニメーションの変更
	mpParent->ChangeAnimation(3, false, 30);
	mState = EState::EATTACK;//状態の種類を攻撃にする
	mAtkCoolTime = 0;
}

void CPlayerAttack::Update()
{
	//アニメーションが終了しているか
	if (mpParent->IsAnimationFinished())
	{
		mAtkCoolTime++;//アニメーションが終了したら加算する

		//アニメーションが終了してmAtkCoolTimeが10以上だったら待機状態にする
		if (mAtkCoolTime > 10)
		{
			mState = EState::EIDLE;
		}
		
	}
}
