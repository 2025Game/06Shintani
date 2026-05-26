#include "CPlayerWalk.h"
#include"CXCharacter.h"

//移動速度
#define VELOCITY 0.1f
//回転速度
#define ROTATIONSPEED 2.0f

void CPlayerWalk::Start(CXCharacter* parent)
{
	//親のポインタを保存
	mpParent = parent;
	//アニメーションの変更
	mpParent->ChangeAnimation(1, true, 60);
	mState = EState::EWALK;//状態の種類を歩くにする
}

void CPlayerWalk::Update()
{
	if (mInput.Key('W'))
	{
		CVector p = mpParent->Position();
		mpParent->Position(p + mpParent->MatrixRotate().VectorZ() * VELOCITY);
		//Wキーが押されているときは歩く状態にする
		mState = EState::EWALK;
		//Aキーで左回転、Dキーで右回転
		if (mInput.Key('D'))
		{
			CVector r = mpParent->Rotation() + CVector(0.0f, -ROTATIONSPEED, 0.0f);
			mpParent->Rotation(r);
		}
		if (mInput.Key('A'))
		{
			CVector r = mpParent->Rotation() + CVector(0.0f, ROTATIONSPEED, 0.0f);
			mpParent->Rotation(r);
		}
		if (mInput.Key('I'))
		{
			//Iキーが押されているときは攻撃状態にする
			mState = EState::EATTACK;
		}
		if (mInput.Key(' '))
		{
			//SPACEキーが押されているときはジャンプ状態にする
			mState = EState::EJUMP;
		}
	}
	else
	{
		//Wキーが押されていないときは待機状態にする
		mState = EState::EIDLE;
	}
	
}
