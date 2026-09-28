#include "CPlayerWalk.h"
#include"CXCharacter.h"
#include"CCamera.h"

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
	//カメラの右方向ベクトルを取得する
	CVector cx;
	//進行すべき前方向のベクトルを取得する
	CVector cz;

	//Wキーで前移動
	if (mInput.Key('W'))
	{
		cx = CCamera::Instance()->ModelViewInverse().VectorX();
		cz = CCamera::Instance()->ModelViewInverse().VectorZ() * -1;
	}
	//Aキーで左移動、
	if (mInput.Key('A'))
	{
		cx = CCamera::Instance()->ModelViewInverse().VectorZ() * -1;
		cz = CCamera::Instance()->ModelViewInverse().VectorX();
	}
	//Sキーで後ろ移動
	if (mInput.Key('S'))
	{
		cx = CCamera::Instance()->ModelViewInverse().VectorX() * -1;
		cz = CCamera::Instance()->ModelViewInverse().VectorZ();
	}
	//Dキーで右移動
	if (mInput.Key('D'))
	{
		cx = CCamera::Instance()->ModelViewInverse().VectorZ();
		cz = CCamera::Instance()->ModelViewInverse().VectorX();
	}
	//プレイヤーの前方向ベクトルを取得する
	CVector fwd = mpParent->CombinedMatrix().VectorZ();
	//内積を計算して、回転量（１０度以内）を求める
	float dx = cx.Dot(fwd);
	float dz = cz.Dot(fwd);
	if (abs(dx) < 0.01f)
	{
		if (dz < 0.0f)
		{
			dx = 1.0f;
		}
	}
	CVector rot(0.0f,dx*10.0f,0.0f);
	//プレイヤーをカメラ方向へ回転させる
	mpParent->Rotation(mpParent->Rotation() + rot);

	
	//カメラを逆回転させる
	CCamera::Instance()->Rotation(CCamera::Instance()->Rotation() - rot);

	if (mInput.Key('W')
		|| mInput.Key('A')
		|| mInput.Key('S')
		|| mInput.Key('D'))
	{
		CVector p = mpParent->Position();
		mpParent->Position(p + mpParent->MatrixRotate().VectorZ() * VELOCITY);
		//W,A,S,Dキーが押されているときは歩く状態にする
		mState = EState::EWALK;
		
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
		//W,A,S,Dキーが押されていないときは待機状態にする
		mState = EState::EIDLE;
	}
	
	
}
